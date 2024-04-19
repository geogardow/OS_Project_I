#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "./memory/read.c"

int main(){
    struct buffer_data data;
    data = read_from_buffer(3);
    printf("Char: %c, Date: %s, Time: %s\n", data.character, data.date, data.time);

    struct stats_data stats;
    stats = read_from_stats();
    printf("Total characters: %d, Total words: %d\n", stats.chars_in_buffer, stats.transferred_chars);

    struct mem_data mem;
    mem = read_from_mem_data();
    printf("Buffer size: %d, Read Counter: %d, Read Flag: %c\n", mem.buffer_size, mem.read_from_file_counter, mem.read_from_file_flag);
    return 0;
}