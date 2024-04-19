#ifndef INIT_H
#define INIT_H

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

char* init_write_memory_block(const char* name, int size);
char* init_read_memory_block(const char* name);

#endif