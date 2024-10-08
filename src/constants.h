#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MAX_ARGS 1
#define MAX_READ_FILES 1
#define MAX_WRITE_FILES 1
#define READ_FILE_NAME "input.txt"
#define WRITE_FILE_NAME "output.txt"
#define SIZEOF_BUFFER_DATA_STRUCT sizeof(struct buffer_data)
#define SIZEOF_SMOBJ_MEM_DATA sizeof(struct mem_data)
#define SIZEOF_SMOBJ_MEM_STATS sizeof(struct stats_data)
#define SMOBJ_NAME_MEM_CHARS  "/mem_chars"
#define SMOBJ_NAME_MEM_DATA  "/mem_data"
#define SMOBJ_NAME_MEM_STATS  "/mem_stats"
#define SMOBJ_SEM_READ_BUFFER  "read_from_buffer_sem"
#define SMOBJ_SEM_WRITE_BUFFER  "write_to_buffer_sem"
#define SMOBJ_SEM_READ_FILE  "read_from_file_sem"
#define SMOBJ_SEM_WRITE_FILE  "write_to_file_sem"
#define SMOBJ_SEM_MEM_DATA  "mem_data_sem"
#define SMOBJ_SEM_MEM_STATS  "mem_stats_sem"


struct buffer_data {
    char character;
    char date[12]; // Formato YYYY-MM-DD
    char time[10];  // Formato HH:MM:SS
};

struct mem_data {
    int buffer_size;
    int read_from_file_counter;
    int write_to_file_counter;
    char read_from_file_flag;
    char write_to_file_flag;
};

struct stats_data {
    double client_blocked_time;
    double reconstructor_blocked_time;
    int transferred_chars;
    int chars_in_buffer;
    int used_memory;
    double client_kernel_time;
    double reconstructor_kernel_time;
    double client_user_time;
    double reconstructor_user_time;
};

#endif
