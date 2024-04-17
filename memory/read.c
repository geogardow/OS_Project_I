#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <creador/creador.h>

void read_mem_chars();

int main(void)
{
   read_mem();
   return 0;
}

void read_mem_chars()
{
   int fd;
   char *ptr;
   struct stat shmobj_st;
   
   fd = shm_open (SMOBJ_NAME_MEM_CHARS,  O_RDONLY  , 00400); /* open s.m object*/
   if(fd == -1)
   {
      printf("Error file descriptor %s\n", strerror(errno));
	   exit(1);
   }
   
   if(fstat(fd, &shmobj_st) == -1)
   {
      printf(" error fstat \n");
	   exit(1);
   }

   // first parameter in mmap is the address
   ptr = mmap(NULL, shmobj_st.st_size, PROT_READ, MAP_SHARED, fd, 0);
   if(ptr == MAP_FAILED)
   {
      printf("Map failed in read process: %s\n", strerror(errno));
      exit(1);
   }
   
   printf("%s \n", ptr);
   close(fd);
}