#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "./memory/write.c"

int main(){
    char ch = 'a';
    write_to_buffer(ch, 3);
    return 0;
}