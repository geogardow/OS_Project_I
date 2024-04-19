#include <stdio.h>
#include <stdbool.h>
#include <semaphore.h>
#include <fcntl.h>
#include "../constants.h"
#include "../memory/read.c"
#include "../memory/write.c"

sem_t *read_from_buffer_sem;
sem_t *write_to_buffer_sem;
sem_t *read_from_file_sem;
sem_t *mem_data_sem;
sem_t *mem_stats_sem;


bool is_finished(struct mem_data data);
char read_from_file(struct mem_data data, char* ptr);
char* init_read_memory_block(const char* name);
char* init_write_memory_block(const char* name, int size);

int main()
{
    read_from_file_sem = sem_open(SMOBJ_SEM_READ_FILE, 0);
    if (read_from_file_sem == SEM_FAILED){
        printf("Error: Could not open read file semaphore");
        exit(1);
    }

    read_from_buffer_sem = sem_open(SMOBJ_SEM_READ_BUFFER, 0);
    if (read_from_buffer_sem == SEM_FAILED){
        printf("Error: Could not open read buffer semaphore");
        exit(1);
    }

    write_to_buffer_sem = sem_open(SMOBJ_SEM_WRITE_BUFFER, 0);
    if (write_to_buffer_sem == SEM_FAILED){
        printf("Error: Could not open write buffer semaphore");
        exit(1);
    }

    mem_data_sem = sem_open(SMOBJ_SEM_MEM_DATA, 0);
    if (mem_data_sem == SEM_FAILED){
        printf("Error: Could not open mem data semaphore");
        exit(1);
    }

    char* ptr_read_mem_data = init_read_memory_block(SMOBJ_NAME_MEM_DATA);
    char* ptr_read_buffer = init_read_memory_block(SMOBJ_NAME_MEM_CHARS);
    char* ptr_read_mem_stats = init_read_memory_block(SMOBJ_NAME_MEM_STATS);
    char* ptr_write_buffer = init_write_memory_block(SMOBJ_NAME_MEM_CHARS, SIZEOF_BUFFER_DATA_STRUCT*100);
    char* ptr_write_mem_data = init_write_memory_block(SMOBJ_NAME_MEM_DATA, SIZEOF_SMOBJ_MEM_DATA);
    char* ptr_write_mem_stats = init_write_memory_block(SMOBJ_NAME_MEM_STATS, SIZEOF_SMOBJ_MEM_STATS);

    while (true)
    {
        sem_wait(read_from_file_sem); // wait read is using resource
        sem_wait(mem_data_sem);

        struct mem_data data = read_from_mem_data(ptr_read_mem_data);
        
        if (is_finished(data)){
            break;
        }

        char ch = read_from_file(data, ptr_write_mem_data);
        sem_post(mem_data_sem);
        sem_post(read_from_file_sem); // resource released

        sem_wait(write_to_buffer_sem); // wait to write buffer
        int buffer_index = 0;
        buffer_index = (data.read_from_file_counter) % data.buffer_size;
        write_to_buffer(ch, buffer_index, ptr_write_buffer);
        sem_post(read_from_buffer_sem); // tell reconstructor that it can read
    }

    sem_close(write_to_buffer_sem);
    sem_close(read_from_buffer_sem);
    sem_close(read_from_file_sem);
    sem_close(mem_data_sem);

}

char* init_read_memory_block(const char* name){
    int fd;
    char *ptr;
    struct stat shmobj_st;
   
    fd = shm_open (name,  O_RDONLY  , 00400); /* open s.m object*/
    if(fd == -1)
    {
        printf("Error file descriptor %s\n", strerror(errno));
        exit(1);
    }
    
    if(fstat(fd, &shmobj_st) == -1)
    {
        printf(" error fstat \n");
        exit(1);
    }

    ptr = mmap(NULL, shmobj_st.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if(ptr == MAP_FAILED)
    {
        printf("Map failed in read process: %s\n", strerror(errno));
        exit(1);
    }
    close(fd);
    return ptr;
}

char* init_write_memory_block(const char* name, int size){
    int fd;
    char *ptr;
    fd = shm_open (name,  O_RDWR  , 00200); /* open s.m object*/
    if(fd == -1)
    {
    printf("Error buffer data file descriptor %s\n", strerror(errno));
    exit(1);
    }

    ptr = mmap(NULL, size, PROT_WRITE, MAP_SHARED, fd, 0);
    if(ptr == MAP_FAILED)
    {
    printf("Map failed in write buffer data process: %s\n", strerror(errno));
    exit(1);
    }

    close(fd);
    return ptr;
}


bool is_finished(struct mem_data mem){
    bool flag;
    flag = (mem.read_from_file_flag == '1');
    return flag;
}

char read_from_file(struct mem_data data, char *ptr_write_mem_data){
    const char* filename = "input.txt";
    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return 1;
    }
    int char_pos = 0;
    char_pos = data.read_from_file_counter;

    // Move the file pointer to char_pos character
    if (fseek(fp, char_pos, SEEK_SET) != 0) {
        printf("Error: fseek failed\n");
        fclose(fp);
        return 1;
    }

    // Read the character at the current file position
    int ch = fgetc(fp);
    if (ch == EOF) {
        printf("End of file reached\n");
        data.read_from_file_flag = '1';
        data.read_from_file_counter = char_pos + 1;
        write_to_mem_data(data, ptr_write_mem_data);
        fclose(fp);
        exit(1);
    }

    data.read_from_file_counter = char_pos + 1;

    write_to_mem_data(data, ptr_write_mem_data);

    fclose(fp);

    return ch;
}
