#include <stdio.h>
#include <stdbool.h> 
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include "../constants.h"
#include "../memory/read.c"


char get_char_from_struct(void);
void write(char ch);
bool is_finished(void);

int main()
{

    write_to_file_sem = sem_open(SMOBJ_SEM_WRITE_FILE, O_CREAT, 0660, 1);
    if (write_to_file_sem == SEM_FAILED){
        printf("Error: Could not open write file semaphore");
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
        sem_wait(read_from_file_sem); // wait to read from buffer
        // read from  buffer
        char character = get_char_from_struct();
        sem_post(write_to_buffer_sem); // the resource is ready to be written

        sem_wait(write_to_file_sem); // wait to write to file
        sem_wait(mem_data_sem);
        struct mem_data data = read_from_mem_data();
        write(character);
        if(is_finished()){
            break;
        }
        sem_post(mem_data_sem)
        sem_post(write_to_file_sem); // release resource for other process
    }
    
    sem_close(write_to_buffer_sem);
    sem_close(write_to_file_sem);
    sem_close(read_from_buffer_sem);
    
    return 0;
}

char get_char_from_struct(void)
{
    char temp = 'a';
    return temp;
}

bool is_finished(struct mem_data data){
    if ((data.write_counter + 1 == data.read_counter) && (data.read_flag)) {
        data.write_flag = '1';
        write_to_mem_data(data);
        return true;
    }
    else{
        data.write_counter = data.write_counter + 1;
        write_to_mem_data(data);
        return false;
    }
}

void write(char ch)
{
    // Open file in write mode
    FILE* copyFile = fopen("output.txt", "a");

    if (copyFile == NULL) {
        printf("Error opening file.\n");
        return; // Exit function if file opening fails
    }

    // Write character to file
    fputc(ch, copyFile);

    // Close file
    fclose(copyFile);
    printf("File copied successfully.\n");
}
