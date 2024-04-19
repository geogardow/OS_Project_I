#include "init.h"

char* init_read_memory_block(const char* name){
    int fd;
    char *ptr;
    struct stat shmobj_st;
   
    fd = shm_open (name,  O_RDONLY  , 00400); /* open s.m object*/
    if(fd == -1)
    {
        printf("Error file descriptor %s\n", strerror(errno));
        exit(1);
    }
    
    if(fstat(fd, &shmobj_st) == -1)
    {
        printf(" error fstat \n");
        exit(1);
    }

    ptr = mmap(NULL, shmobj_st.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if(ptr == MAP_FAILED)
    {
        printf("Map failed in read process: %s\n", strerror(errno));
        exit(1);
    }
    close(fd);
    return ptr;
}

char* init_write_memory_block(const char* name, int size){
    int fd;
    char *ptr;
    fd = shm_open (name,  O_RDWR  , 00200); /* open s.m object*/
    if(fd == -1)
    {
    printf("Error buffer data file descriptor %s\n", strerror(errno));
    exit(1);
    }

    ptr = mmap(NULL, size, PROT_WRITE, MAP_SHARED, fd, 0);
    if(ptr == MAP_FAILED)
    {
    printf("Map failed in write buffer data process: %s\n", strerror(errno));
    exit(1);
    }

    close(fd);
    return ptr;
}