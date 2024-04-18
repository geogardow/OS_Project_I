#include <stdio.h>
#include <stdbool.h>
#include <semaphore.h>
#include <fcntl.h>
#include "../constants.h"
#include "../memory/read.c"

sem_t *read_from_buffer_sem;
sem_t *write_to_buffer_sem;
sem_t *read_from_file_sem;
sem_t *mem_data_sem;
sem_t *mem_stats_sem;


bool is_finished(struct mem_data data);
int read_char(struct mem_data data);

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

    while (true)
    {
        sem_wait(read_from_file_sem); // wait read is using resource
        sem_wait(mem_data_sem);
        struct mem_data data = read_from_mem_data();
        
        if (is_finished(data)){
            break;
        }

        read_char(data);
        sem_post(mem_data_sem);
        sem_post(read_from_file_sem); // resource released

        sem_wait(write_to_buffer_sem); // wait to write buffer
        // write to buffer
        sem_post(read_from_buffer_sem); // tell reconstructor that it can read

    }

    sem_close(write_to_buffer_sem);
    sem_close(read_from_buffer_sem);
    sem_close(read_from_file_sem);
    sem_close(mem_data_sem);

}

bool is_finished(struct mem_data mem){
    bool flag;
    flag = (mem.read_flag == '1');
    return flag;
}

int read_char(struct mem_data data){
    const char* filename = "input.txt";
    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return 1;
    }

    int char_pos = data.read_counter;

    // Move the file pointer to char_pos character
    if (fseek(fp, char_pos, SEEK_SET) != 0) {
        printf("Error: fseek failed\n");
        fclose(fp);
        return 1;
    }

    // Read the character at the current file position
    int ch = fgetc(fp);
    if (ch == EOF) {
        printf("Error: End of file reached\n");
        data.read_flag = '1';
        write_to_mem_data(data);
        fclose(fp);
        return 1;
    }

    data.read_counter = char_pos + 1;

    write_to_mem_data(data);
    
    printf("The character in the file is: %c\n", (char)ch);

    // Close the file
    fclose(fp);

    return 0;
}