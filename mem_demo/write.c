/*
   It writes to a previously created memory object "/myMemoryObj"
   to be compiled with "-lrt"
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
 
#define SMOBJ_NAME  "/myMemoryObj"

void write_mem(char ch, int address);

int main(void)
{
   char ch = 'h';
   int address = 0x0;
   write_mem(ch, address);
   return 0;
}

void write_mem(char ch, int address)
{
   int fd;
   char *ptr;
   
   fd = shm_open (SMOBJ_NAME,  O_RDWR  , 00200); /* open s.m object*/
   if(fd == -1)
   {
      printf("Error file descriptor %s\n", strerror(errno));
	   exit(1);
   }
   
   ptr = mmap((void*) address, sizeof(ch), PROT_WRITE, MAP_SHARED, fd, 0);
   if(ptr == MAP_FAILED)
   {
      printf("Map failed in write process: %s\n", strerror(errno));
      exit(1);
   }
   
   memcpy(ptr,ch, sizeof(ch));
   printf("%d \n", (int)sizeof(ch));
   close(fd);
}