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
#include <time.h>

sem_t *read_from_buffer_sem;
sem_t *write_to_buffer_sem;
sem_t *read_from_file_sem;
sem_t *mem_data_sem;
sem_t *mem_stats_sem;

clock_t start_blocked_time;
clock_t end_blocked_time;
clock_t start_kernel_time;
clock_t end_kernel_time;
clock_t start_user_time;
clock_t end_user_time;

int CHARS_TRANSFERRED = 0;

double time_blocked = 0;
double time_kernel = 0;
double time_user = 0;

int MODE;

bool is_finished(struct mem_data data);
bool is_read_finished(struct mem_data mem);
char read_from_file(struct mem_data data, char *ptr_write_mem_data, char *ptr_read_mem_data);
void save_stats(char *ptr_write_mem_stats, char *ptr_read_mem_stats);

#endif