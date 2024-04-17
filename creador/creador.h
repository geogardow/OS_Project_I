#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>

struct buffer_data {
    char character;
    char date[11]; // Formato YYYY-MM-DD
    char time[6];  // Formato HH:MM
};

struct mem_data {
    int buffer_size;
    int read_counter;
    int write_counter;
    char read_flag;
    char write_flag;
};

struct stats_data {
    float client_blocked_time;
    float reconstructor_blocked_time;
    int transferred_chars;
    int chars_in_buffer;
    int used_memory;
    float client_kernel_time;
    float reconstructor_kernel_time;
    float client_user_time;
    float reconstructor_user_time;
};

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

int SIZEOF_SMOBJ_MEM_CHARS;
int CHARS_IN_BUFFER;

sem_t *read_from_buffer_sem;
sem_t *write_to_buffer_sem;
sem_t *read_from_file_sem;
sem_t *write_to_file_sem;
