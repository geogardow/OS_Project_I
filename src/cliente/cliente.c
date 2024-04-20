#include "cliente.h"

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
        
        sem_wait(read_from_file_sem);
        sem_wait(mem_data_sem);
        struct mem_data data = read_from_mem_data(ptr_read_mem_data);

        if (is_finished(data)){
            printf("Llegúe");
            printf("Buffer size: %d, Read from file counter: %d, Write to file counter: %d, Read from file flag: %c, Write to file flag: %c\n", data.buffer_size, data.read_from_file_counter, data.write_to_file_counter, data.read_from_file_flag, data.write_to_file_flag);
            sem_post(mem_data_sem);
            sem_post(read_from_file_sem);
            break;
        }

        printf("Buffer size: %d, Read from file counter: %d, Write to file counter: %d, Read from file flag: %c, Write to file flag: %c\n", data.buffer_size, data.read_from_file_counter, data.write_to_file_counter, data.read_from_file_flag, data.write_to_file_flag);
        char ch = read_from_file(data, ptr_write_mem_data, ptr_read_mem_data);
        sem_post(mem_data_sem);

        sem_wait(write_to_buffer_sem);
        int buffer_index = (data.read_from_file_counter) % data.buffer_size;
        write_to_buffer(ch, buffer_index, ptr_write_buffer);
        sem_post(read_from_buffer_sem);  

        sem_post(read_from_file_sem);
    }
}

bool is_finished(struct mem_data mem){
    bool flag;
    if ((mem.write_to_file_counter == mem.read_from_file_counter) && (mem.read_from_file_flag == '1')) 
        flag = true;
    else
        flag = false;
    return flag;
}

bool is_read_finished(struct mem_data mem){
    bool flag;
    flag = (mem.read_from_file_flag == '1');
    return flag;
}

char read_from_file(struct mem_data data, char *ptr_write_mem_data, char *ptr_read_mem_data){
    const char* filename = "input.txt";
    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return 1;
    }

    int char_pos = data.read_from_file_counter;

    // Move the file pointer to char_pos character
    if (fseek(fp, char_pos, SEEK_SET) != 0) {
        printf("Error: fseek failed\n");
        fclose(fp);
    }

    // Read the character at the current file position
    int ch = fgetc(fp);
    if (ch == EOF) {
        data.read_from_file_flag = '1';
        write_to_mem_data(data, ptr_write_mem_data);
        printf("File read successfully\n");
        fclose(fp);
        return ' ';
    }

    printf("Char: %c\n", ch);
    data.read_from_file_counter = char_pos + 1;
    write_to_mem_data(data, ptr_write_mem_data);

    fclose(fp);

    return ch;
}
