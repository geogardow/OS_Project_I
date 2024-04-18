#ifndef WRITE_H
#define WRITE_H

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

void write_to_buffer(char ch, int buffer_index);
void write_to_stats(struct stats_data stats);
void write_to_mem_data(struct mem_data mem);

#endif 