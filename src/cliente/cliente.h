#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdbool.h>
#include <semaphore.h>
#include <fcntl.h>
#include "../constants.h"
#include "../memory/read.c"
#include "../memory/write.c"
#include "../memory/init.c"

sem_t *read_from_buffer_sem;
sem_t *write_to_buffer_sem;
sem_t *read_from_file_sem;
sem_t *mem_data_sem;
sem_t *mem_stats_sem;

bool is_finished(struct mem_data data);
bool is_read_finished(struct mem_data mem);
char read_from_file(struct mem_data data, char *ptr_write_mem_data, char *ptr_read_mem_data);

#endif