#include "creador.h"


int main(int argc, char *argv[])
{
    if (argc != MAX_ARGS + 1) {
        printf("Error, only one argument is allowed\n");
        return 1;
    }

    CHARS_IN_BUFFER = atoi(argv[1]);
    SIZEOF_SMOBJ_MEM_CHARS = SIZEOF_BUFFER_DATA_STRUCT * CHARS_IN_BUFFER;

    create_memory(SMOBJ_NAME_MEM_CHARS, SIZEOF_SMOBJ_MEM_CHARS);
    create_memory(SMOBJ_NAME_MEM_DATA, SIZEOF_SMOBJ_MEM_DATA);
    create_memory(SMOBJ_NAME_MEM_STATS, SIZEOF_SMOBJ_MEM_STATS);

    char* ptr_read_mem_data = init_read_memory_block(SMOBJ_NAME_MEM_DATA);
    char* ptr_read_buffer = init_read_memory_block(SMOBJ_NAME_MEM_CHARS);
    char* ptr_read_mem_stats = init_read_memory_block(SMOBJ_NAME_MEM_STATS);
    char* ptr_write_buffer = init_write_memory_block(SMOBJ_NAME_MEM_CHARS, SIZEOF_SMOBJ_MEM_CHARS);
    char* ptr_write_mem_data = init_write_memory_block(SMOBJ_NAME_MEM_DATA, SIZEOF_SMOBJ_MEM_DATA);
    char* ptr_write_mem_stats = init_write_memory_block(SMOBJ_NAME_MEM_STATS, SIZEOF_SMOBJ_MEM_STATS);

    struct mem_data mem_data_instance;
    struct stats_data stats_data_instance;
    build_mem_data_instance(&mem_data_instance);
    build_stats_data_instance(&stats_data_instance);

    write_to_mem_data(mem_data_instance, ptr_write_mem_data);
    write_to_stats(stats_data_instance, ptr_write_mem_stats);

    init_semaphores();


    print_chars_memory(ptr_read_buffer, ptr_read_mem_data);

    return 0;

}

void print_chars_memory(char *ptr_read_mem_buffer, char* ptr_read_mem_data){
    while (true)
    {
        struct mem_data mem_data_instance = read_from_mem_data(ptr_read_mem_data);
        if (mem_data_instance.read_from_file_flag == '1' && mem_data_instance.write_to_file_flag == '1')
        {
            break;
        }
        for(int i = 0; i < CHARS_IN_BUFFER; i++){
            struct buffer_data *buffer_data_instance = read_from_buffer(i, ptr_read_mem_buffer);
        }
        // Flush stdout to ensure all output is printed to the console
        fflush(stdout);

        // Check for new data every 1 second
        sleep(1);
        system("clear");   
    }
    
}

void create_memory(const char *name, int size){
    int fd;
    fd = shm_open(name, O_CREAT | O_RDWR | O_TRUNC  , 00700); /* create s.m object*/
    if(fd == -1)
    {
        printf("Error file descriptor \n");
        exit(1);
    }
    if(ftruncate(fd, size) == -1)
    {
        printf("Error shared memory cannot be resized \n");
        exit(1);
    }
    
    close(fd);
}

void init_semaphores(){
    sem_unlink(SMOBJ_SEM_READ_BUFFER);
    sem_unlink(SMOBJ_SEM_WRITE_BUFFER);
    sem_unlink(SMOBJ_SEM_READ_FILE);
    sem_unlink(SMOBJ_SEM_WRITE_FILE);
    sem_unlink(SMOBJ_SEM_MEM_DATA);
    sem_unlink(SMOBJ_SEM_MEM_STATS);

    read_from_buffer_sem = sem_open(SMOBJ_SEM_READ_BUFFER, O_CREAT, S_IRUSR | S_IWUSR, 0);
    write_to_buffer_sem = sem_open(SMOBJ_SEM_WRITE_BUFFER, O_CREAT, S_IRUSR | S_IWUSR, CHARS_IN_BUFFER);
    read_from_file_sem = sem_open(SMOBJ_SEM_READ_FILE, O_CREAT, S_IRUSR | S_IWUSR, MAX_READ_FILES);
    write_to_file_sem = sem_open(SMOBJ_SEM_WRITE_FILE, O_CREAT, S_IRUSR | S_IWUSR, MAX_WRITE_FILES);
    mem_data_sem = sem_open(SMOBJ_SEM_MEM_DATA, O_CREAT, S_IRUSR | S_IWUSR, 1);
    mem_stats_sem = sem_open(SMOBJ_SEM_MEM_STATS, O_CREAT, S_IRUSR | S_IWUSR, 1);

}

void build_mem_data_instance(struct mem_data *mem_data_instance){
    mem_data_instance->buffer_size = CHARS_IN_BUFFER; // Tamaño del buffer circular
    mem_data_instance->read_from_file_counter = 0;
    mem_data_instance->write_to_file_counter = 0;
    mem_data_instance->read_from_file_flag = '0'; // Flag como caracter '0' (no leído)
    mem_data_instance->write_to_file_flag = '0'; // Flag como caracter '0' (no escrito)
}

void build_stats_data_instance(struct stats_data *stats_data_instance){
    stats_data_instance->client_blocked_time = 0;
    stats_data_instance->reconstructor_blocked_time = 0;
    stats_data_instance->transferred_chars = 0;
    stats_data_instance->chars_in_buffer = CHARS_IN_BUFFER;
    stats_data_instance->used_memory = SIZEOF_SMOBJ_MEM_CHARS + SIZEOF_SMOBJ_MEM_DATA + SIZEOF_SMOBJ_MEM_STATS + sizeof(sem_t) * 6;
    stats_data_instance->client_kernel_time = 0;
    stats_data_instance->reconstructor_kernel_time = 0;
    stats_data_instance->client_user_time = 0;
    stats_data_instance->reconstructor_user_time = 0;
}