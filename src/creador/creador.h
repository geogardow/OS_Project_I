#ifndef CREADOR_H
#define CREADOR_H

#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#include "../memory/write.c"
#include "../memory/read.c"
#include "../memory/init.c"
#include "../constants.h"
#include <time.h>

sem_t *read_from_buffer_sem;
sem_t *write_to_buffer_sem;
sem_t *read_from_file_sem;
sem_t *write_to_file_sem;
sem_t *mem_data_sem;
sem_t *mem_stats_sem;


int SIZEOF_SMOBJ_MEM_CHARS;
int CHARS_IN_BUFFER;

void create_memory(const char *name, int size);
void init_semaphores();
void build_mem_data_instance(struct mem_data *mem_data_instance);
void build_stats_data_instance(struct stats_data *stats_data_instance);
void print_chars_memory(char *ptr_read_mem_buffer, char* ptr_read_mem_data);

#endif
