#ifndef READ_H
#define READ_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include "../constants.h"

struct buffer_data* read_from_buffer(int buffer_index, char* ptr);
struct stats_data read_from_stats(char* ptr);
struct mem_data read_from_mem_data(char* ptr);

#endif 