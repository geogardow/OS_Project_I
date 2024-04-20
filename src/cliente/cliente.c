#include "cliente.h"

int main(int argc, char *argv[])
{
    if (argc != MAX_ARGS + 1) {
        printf("Error, only one argument is allowed\n");
        return 1;
    }

    MODE = atoi(argv[1]);

    start_kernel_time = clock();
    start_user_time = clock();

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

    mem_stats_sem = sem_open(SMOBJ_SEM_MEM_STATS, 0);
    if (mem_stats_sem == SEM_FAILED){
        printf("Error: Could not open stats data semaphore");
        exit(1);
    }

    char* ptr_read_mem_data = init_read_memory_block(SMOBJ_NAME_MEM_DATA);
    char* ptr_read_buffer = init_read_memory_block(SMOBJ_NAME_MEM_CHARS);
    char* ptr_read_mem_stats = init_read_memory_block(SMOBJ_NAME_MEM_STATS);
    char* ptr_write_mem_data = init_write_memory_block(SMOBJ_NAME_MEM_DATA, SIZEOF_SMOBJ_MEM_DATA);
    char* ptr_write_mem_stats = init_write_memory_block(SMOBJ_NAME_MEM_STATS, SIZEOF_SMOBJ_MEM_STATS);

    end_kernel_time = clock();
    time_kernel += ((double) (end_kernel_time - start_kernel_time)) / CLOCKS_PER_SEC;

    sem_wait(mem_data_sem);
    start_kernel_time = clock();
    struct mem_data data = read_from_mem_data(ptr_read_mem_data);
    char* ptr_write_buffer = init_write_memory_block(SMOBJ_NAME_MEM_CHARS, SIZEOF_BUFFER_DATA_STRUCT*data.buffer_size);
    end_kernel_time = clock();
    time_kernel += ((double) (end_kernel_time - start_kernel_time)) / CLOCKS_PER_SEC;
    sem_post(mem_data_sem);

    while (true)
    {
        if (MODE == 1)
        {
            printf("Press Enter to continue...\n");
            getchar();
        }
        
        start_blocked_time = clock();
        sem_wait(read_from_file_sem);
        sem_wait(mem_data_sem);
        end_blocked_time = clock();
        
        time_blocked += ((double) (end_blocked_time - start_blocked_time)) / CLOCKS_PER_SEC;

        struct mem_data data = read_from_mem_data(ptr_read_mem_data);

        if (is_finished(data)){
            sem_post(mem_data_sem);
            sem_post(read_from_file_sem);
            save_stats(ptr_write_mem_stats, ptr_read_mem_stats);
            break;
        }

        start_kernel_time = clock();
        char ch = read_from_file(data, ptr_write_mem_data, ptr_read_mem_data);
        end_kernel_time = clock();
        time_kernel += ((double) (end_kernel_time - start_kernel_time)) / CLOCKS_PER_SEC;

        sem_post(mem_data_sem);

        sem_wait(write_to_buffer_sem);
        int buffer_index = (data.read_from_file_counter) % data.buffer_size;

        start_kernel_time = clock();
        write_to_buffer(ch, buffer_index, ptr_write_buffer);
        end_kernel_time = clock();
        time_kernel += ((double) (end_kernel_time - start_kernel_time)) / CLOCKS_PER_SEC;

        sem_post(read_from_buffer_sem);  

        sem_post(read_from_file_sem);
    }
}

bool is_finished(struct mem_data mem){
    bool flag;
    if ((mem.write_to_file_counter == mem.read_from_file_counter) && (mem.read_from_file_flag == '1')){
        CHARS_TRANSFERRED = mem.write_to_file_counter;
        flag = true;
    } else {
        flag = false;
    }
    return flag;
}

bool is_read_finished(struct mem_data mem){
    bool flag;
    flag = (mem.read_from_file_flag == '1');
    return flag;
}

char read_from_file(struct mem_data data, char *ptr_write_mem_data, char *ptr_read_mem_data){
    const char* filename = "input.txt";
    FILE* input_file = fopen(filename, "r");
    const char* output_filename = "live_read.txt";
    FILE* output_file = fopen(output_filename, "w");

    if (input_file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return 1;
    }

    if (output_file == NULL) {
        printf("Error: Could not open file %s\n", output_filename);
        exit(1);
    }

    int char_pos = data.read_from_file_counter;

    // Move the file pointer to char_pos character
    if (fseek(input_file, char_pos, SEEK_SET) != 0) {
        printf("Error: fseek failed\n");
        fclose(input_file);
    }

    // Read the character at the current file position
    int ch = fgetc(input_file);
    if (ch == EOF) {
        data.read_from_file_flag = '1';
        write_to_mem_data(data, ptr_write_mem_data);
        printf("File read successfully\n");
        fclose(input_file);
        return ' ';
    }

    int current_pos = char_pos + 1;

    // Move the file pointer to char_pos character
    if (fseek(input_file, current_pos, SEEK_SET) != 0) {
        printf("Error: fseek failed\n");
        fclose(input_file);
    }

    int ch_out;
    while ((ch_out = fgetc(input_file)) != EOF) {
        fputc(ch_out, output_file);
    }

    data.read_from_file_counter = current_pos;
    write_to_mem_data(data, ptr_write_mem_data);

    fclose(input_file);
    fclose(output_file);

    return ch;
}

void save_file_progress(int char_pos){
    
}

void save_stats(char *ptr_write_mem_stats, char *ptr_read_mem_stats){
    end_user_time = clock();
    time_user += ((double) (end_user_time - start_user_time)) / CLOCKS_PER_SEC;
    time_user -= time_kernel;
    sem_wait(mem_stats_sem);
    struct stats_data stats = read_from_stats(ptr_read_mem_stats);
    stats.client_blocked_time = stats.client_blocked_time + time_blocked;
    stats.client_user_time = stats.client_user_time + time_user;
    stats.client_kernel_time = stats.client_kernel_time + time_kernel;
    stats.transferred_chars = CHARS_TRANSFERRED;
    write_to_stats(stats, ptr_write_mem_stats);
    sem_post(mem_stats_sem);
}