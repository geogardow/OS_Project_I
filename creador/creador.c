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

    init_semaphores();

    struct mem_data mem_data_instance;
    build_data_instance(&mem_data_instance);
    print_data_struct(&mem_data_instance);

    return 0;
}

int create_memory(const char *name, int size){
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

int init_semaphores(){
    read_from_buffer_sem = sem_open("read_from_buffer_sem", O_CREAT, S_IRUSR | S_IWUSR, 0);
    write_to_buffer_sem = sem_open("write_to_buffer_sem", O_CREAT, S_IRUSR | S_IWUSR, CHARS_IN_BUFFER);
    read_from_file_sem = sem_open("read_from_file_sem", O_CREAT, S_IRUSR | S_IWUSR, MAX_READ_FILES);
    write_to_file_sem = sem_open("write_to_file_sem", O_CREAT, S_IRUSR | S_IWUSR, MAX_WRITE_FILES);

}

int build_data_instance(struct mem_data *mem_data_instance){
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