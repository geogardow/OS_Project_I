#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "./memory/read.c"

int main(){
    struct buffer_data data;
    data = read_from_buffer(3);
    printf("Char: %c, Date: %s, Time: %s\n", data.character, data.date, data.time);
    return 0;
}