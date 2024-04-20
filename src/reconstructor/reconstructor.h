#ifndef RECONSTRUCTOR_H
#define RECONSTRUCTOR_H

#include <stdio.h>
#include <stdbool.h> 
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include "../constants.h"
#include "../memory/read.c"
#include "../memory/write.c"
#include "../memory/init.c"

sem_t *read_from_buffer_sem;
sem_t *write_to_buffer_sem;
sem_t *write_to_file_sem;
sem_t *mem_data_sem;
sem_t *mem_stats_sem;
sem_t *read_from_file_sem;

int MODE;

void write_to_file(char ch);
bool is_finished(struct mem_data data, char* ptr_write_mem_data);

#endif