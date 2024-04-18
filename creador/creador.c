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
    
    struct mem_data mem_data_instance;
    struct stats_data stats_data_instance;
    build_mem_data_instance(&mem_data_instance);
    build_stats_data_instance(&stats_data_instance);

    write_to_memdata(mem_data_instance);
    write_to_stats(stats_data_instance);

    init_semaphores();

    return 0;
}

void create_memory(const char *name, int size){
    int fd;
    fd = shm_open(name, O_CREAT | O_RDWR  , 00700); /* create s.m object*/
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
    mem_data_instance->read_counter = 0;
    mem_data_instance->write_counter = 0;
    mem_data_instance->read_flag = '0'; // Flag como caracter '0' (no leído)
    mem_data_instance->write_flag = '0'; // Flag como caracter '0' (no escrito)
}

void print_data_struct(struct mem_data *data) {
    printf("Buffer Size: %d\n", data->buffer_size);
    printf("Read Counter: %d\n", data->read_counter);
    printf("Write Counter: %d\n", data->write_counter);
    printf("Read Flag: %c\n", data->read_flag);
    printf("Write Flag: %c\n", data->write_flag);
}

void build_stats_data_instance(struct stats_data *stats_data_instance){
    stats_data_instance->client_blocked_time = 0;
    stats_data_instance->reconstructor_blocked_time = 0;
    stats_data_instance->transferred_chars = 0;
    stats_data_instance->chars_in_buffer = 0;
    stats_data_instance->used_memory = 0;
    stats_data_instance->client_kernel_time = 0;
    stats_data_instance->reconstructor_kernel_time = 0;
    stats_data_instance->client_user_time = 0;
    stats_data_instance->reconstructor_user_time = 0;
}