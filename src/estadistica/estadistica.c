#include "estadistica.h"

int main(){
    char* ptr_read_mem_stats = init_read_memory_block(SMOBJ_NAME_MEM_STATS);
    struct stats_data stats = read_from_stats(ptr_read_mem_stats);
    printf("Client blocked time: %f s\n", stats.client_blocked_time);
    printf("Reconstructor blocked time: %f s\n", stats.reconstructor_blocked_time);
    printf("Transferred chars: %d\n", stats.transferred_chars);
    printf("Chars in buffer: %d\n", stats.chars_in_buffer);
    printf("Used memory: %d bytes\n", stats.used_memory);
    printf("Client kernel time: %f s\n", stats.client_kernel_time);
    printf("Reconstructor kernel time: %f s\n", stats.reconstructor_kernel_time);
    printf("Client user time: %f s\n", stats.client_user_time);
    printf("Reconstructor user time: %f s\n", stats.reconstructor_user_time);
    return 0;
}