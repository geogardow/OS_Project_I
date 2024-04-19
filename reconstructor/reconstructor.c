#include <stdio.h>
#include <stdbool.h> 
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include "../constants.h"
#include "../memory/read.c"
#include "../memory/write.c"

sem_t *read_from_buffer_sem;
sem_t *write_to_buffer_sem;
sem_t *write_to_file_sem;
sem_t *mem_data_sem;
sem_t *mem_stats_sem;

void write_to_file(char ch);
bool is_finished(struct mem_data data, char* ptr_write_mem_data);
char* init_read_memory_block(const char* name);
char* init_write_memory_block(const char* name, int size);

int main()
{

    write_to_file_sem = sem_open(SMOBJ_SEM_WRITE_FILE, O_CREAT, 0660, 1);
    if (write_to_file_sem == SEM_FAILED){
        printf("Error: Could not open write_to_file file semaphore");
        exit(1);
    }

    read_from_buffer_sem = sem_open(SMOBJ_SEM_READ_BUFFER, 0);
    if (read_from_buffer_sem == SEM_FAILED){
        printf("Error: Could not open read buffer semaphore");
        exit(1);
    }

    write_to_buffer_sem = sem_open(SMOBJ_SEM_WRITE_BUFFER, 0);
    if (write_to_buffer_sem == SEM_FAILED){
        printf("Error: Could not open write_to_file buffer semaphore");
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
    char* ptr_write_buffer = init_write_memory_block(SMOBJ_NAME_MEM_CHARS, SIZEOF_BUFFER_DATA_STRUCT*5);
    char* ptr_write_mem_data = init_write_memory_block(SMOBJ_NAME_MEM_DATA, SIZEOF_SMOBJ_MEM_DATA);
    char* ptr_write_mem_stats = init_write_memory_block(SMOBJ_NAME_MEM_STATS, SIZEOF_SMOBJ_MEM_STATS);

    while (true)
    {
        sem_wait(read_from_buffer_sem); // wait to read from buffer
        sem_wait(mem_data_sem);

        struct mem_data data = read_from_mem_data(ptr_read_mem_data);

        int buffer_index = data.write_to_file_counter % data.buffer_size;
        struct buffer_data* data_from_buffer_ptr = read_from_buffer(buffer_index, ptr_read_buffer);

        char character = data_from_buffer_ptr->character;


        if(is_finished(data, ptr_write_mem_data)){
            break;
        }

        sem_post(mem_data_sem);
        sem_post(write_to_buffer_sem); // the resource is ready to be written

        sem_wait(write_to_file_sem); // wait to write_to_file to file
        write_to_file(character);
        sem_post(write_to_file_sem); // release resource for other process

    }
    
    sem_close(write_to_file_sem);
    sem_close(read_from_buffer_sem);
    sem_close(mem_data_sem);
    sem_close(write_to_buffer_sem);
    
    return 0;
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

bool is_finished(struct mem_data data, char* ptr_write_mem_data){
    if ((data.write_to_file_counter == data.read_from_file_counter) && (data.read_from_file_flag == '1')) {
        data.write_to_file_flag = '1';
        write_to_mem_data(data, ptr_write_mem_data);
        printf("File copied successfully.\n");

        return true;
    }
    else{
        data.write_to_file_counter = data.write_to_file_counter + 1;
        write_to_mem_data(data, ptr_write_mem_data);
        return false;
    }
}

void write_to_file(char ch)
{
    // Open file in write_to_file mode
    FILE* copyFile = fopen("output.txt", "a");

    if (copyFile == NULL) {
        printf("Error opening file.\n");
        return; // Exit function if file opening fails
    }

    // write_to_file character to file
    fputc(ch, copyFile);

    // Close file
    fclose(copyFile);
}
