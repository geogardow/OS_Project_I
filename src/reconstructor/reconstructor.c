#include "reconstructor.h"

int main(int argc, char *argv[])
{
    if (argc != MAX_ARGS + 1) {
        printf("Error, only one argument is allowed\n");
        return 1;
    }

    MODE = atoi(argv[1]);
    
    read_from_file_sem = sem_open(SMOBJ_SEM_READ_FILE, 0);
    if (read_from_file_sem == SEM_FAILED){
        printf("Error: Could not open read file semaphore");
        exit(1);
    }

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
    char* ptr_write_mem_data = init_write_memory_block(SMOBJ_NAME_MEM_DATA, SIZEOF_SMOBJ_MEM_DATA);
    char* ptr_write_mem_stats = init_write_memory_block(SMOBJ_NAME_MEM_STATS, SIZEOF_SMOBJ_MEM_STATS);

    sem_wait(mem_data_sem);
    struct mem_data data = read_from_mem_data(ptr_read_mem_data);
    char* ptr_write_buffer = init_write_memory_block(SMOBJ_NAME_MEM_CHARS, SIZEOF_BUFFER_DATA_STRUCT*data.buffer_size);
    sem_post(mem_data_sem);

    while (true)
    {
        if (MODE == 1)
        {
            printf("Press Enter to continue...\n");
            getchar();
        }

        sem_wait(read_from_buffer_sem);
        sem_wait(mem_data_sem);
        struct mem_data data = read_from_mem_data(ptr_read_mem_data);
        
        if(is_finished(data, ptr_write_mem_data)){
            sem_post(mem_data_sem);
            sem_post(write_to_buffer_sem); // the resource is ready to be written
            break;
        }

        sem_wait(write_to_file_sem); // wait to write_to_file to file
        printf("Buffer size: %d, Read from file counter: %d, Write to file counter: %d, Read from file flag: %c, Write to file flag: %c\n", data.buffer_size, data.read_from_file_counter, data.write_to_file_counter, data.read_from_file_flag, data.write_to_file_flag);
        int buffer_index = data.write_to_file_counter % data.buffer_size;
        struct buffer_data* data_from_buffer_ptr = read_from_buffer(buffer_index, ptr_read_buffer);
        char character = data_from_buffer_ptr->character;

        sem_post(mem_data_sem);
        sem_post(write_to_buffer_sem); // the resource is ready to be written

        write_to_file(character);
        sem_post(write_to_file_sem); // release resource for other process   
    }
    
    sem_close(write_to_file_sem);
    sem_close(read_from_buffer_sem);
    sem_close(mem_data_sem);
    sem_close(write_to_buffer_sem);
    sem_close(read_from_file_sem);
    
    return 0;
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
