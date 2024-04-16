#include <creador.h>

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
    sem_init(&read_from_buffer_sem, 0, CHARS_IN_BUFFER);
    sem_init(&write_to_buffer_sem, 0, CHARS_IN_BUFFER);
    sem_init(&read_from_data_sem, 0, MAX_READ_FILES);
    sem_init(&write_to_data_sem, 0, MAX_WRITE_FILES);
    
}