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
bool is_finished(struct mem_data data);

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

    while (true)
    {
        sem_wait(mem_data_sem);
        sem_wait(read_from_buffer_sem); // wait to read from buffer

        struct mem_data data = read_from_mem_data();
        int buffer_index = data.write_to_file_counter % data.buffer_size;
        struct buffer_data data_from_buffer = read_from_buffer(buffer_index);
        char character = data_from_buffer.character;

        if(is_finished(data)){
            break;
        }

        sem_post(write_to_buffer_sem); // the resource is ready to be written
        sem_post(mem_data_sem);

        sem_wait(write_to_file_sem); // wait to write_to_file to file
        write_to_file(character);
        sem_post(write_to_file_sem); // release resource for other process
    }
    
    sem_close(write_to_buffer_sem);
    sem_close(write_to_file_sem);
    sem_close(read_from_buffer_sem);
    sem_close(mem_data_sem);
    
    return 0;
}

bool is_finished(struct mem_data data){
    if ((data.write_to_file_counter == data.read_from_file_counter) && (data.read_from_file_flag)) {
        data.write_to_file_flag = '1';
        write_to_mem_data(data);
        return true;
    }
    else{
        data.write_to_file_counter = data.write_to_file_counter + 1;
        write_to_mem_data(data);
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
    printf("File copied successfully.\n");
}
