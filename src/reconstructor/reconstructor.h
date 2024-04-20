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
#include <time.h>

sem_t *read_from_buffer_sem;
sem_t *write_to_buffer_sem;
sem_t *write_to_file_sem;
sem_t *mem_data_sem;
sem_t *mem_stats_sem;
sem_t *read_from_file_sem;

clock_t start_blocked_time;
clock_t end_blocked_time;
clock_t start_kernel_time;
clock_t end_kernel_time;
clock_t start_user_time;
clock_t end_user_time;

double time_blocked = 0;
double time_kernel = 0;
double time_user = 0;

int MODE;

void write_to_file(char ch);
bool is_finished(struct mem_data data, char* ptr_write_mem_data);
void save_stats(char *ptr_write_mem_stats, char *ptr_read_mem_stats);

#endif