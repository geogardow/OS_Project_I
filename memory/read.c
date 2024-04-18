#include "read.h"

struct buffer_data read_from_buffer(int buffer_index)
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

   ptr = mmap(NULL, shmobj_st.st_size, PROT_READ, MAP_SHARED, fd, 0);
   if(ptr == MAP_FAILED)
   {
      printf("Map failed in read process: %s\n", strerror(errno));
      exit(1);
   }

   char *address = ptr + (buffer_index * SIZEOF_BUFFER_DATA_STRUCT);

   struct buffer_data *data = NULL;
   data = (struct buffer_data *)malloc(SIZEOF_BUFFER_DATA_STRUCT);
   if (data == NULL) {
      printf("Error: Memory allocation failed\n");
      exit(1);
   }
   
   data = (struct buffer_data *)address;
   printf("Char: %c, Date: %s, Time: %s\n", data->character, data->date, data->time);
   close(fd);

   return *data;
}

struct stats_data read_from_stats()
{
   int fd;
   char *ptr;
   struct stat shmobj_st;
   
   fd = shm_open (SMOBJ_NAME_MEM_STATS,  O_RDONLY  , 00400); /* open s.m object*/
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

   ptr = mmap(NULL, shmobj_st.st_size, PROT_READ, MAP_SHARED, fd, 0);
   if(ptr == MAP_FAILED)
   {
      printf("Map failed in read process: %s\n", strerror(errno));
      exit(1);
   }

   struct stats_data *data = NULL;
   data = (struct stats_data *)malloc(SIZEOF_BUFFER_DATA_STRUCT);
   if (data == NULL) {
      printf("Error: Memory allocation failed\n");
      exit(1);
   }
   
   data = (struct stats_data *)ptr;
   close(fd);

   return *data;
}

struct mem_data read_from_mem_data()
{
   int fd;
   char *ptr;
   struct stat shmobj_st;
   
   fd = shm_open (SMOBJ_NAME_MEM_DATA,  O_RDONLY  , 00400); /* open s.m object*/
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

   ptr = mmap(NULL, shmobj_st.st_size, PROT_READ, MAP_SHARED, fd, 0);
   if(ptr == MAP_FAILED)
   {
      printf("Map failed in read process: %s\n", strerror(errno));
      exit(1);
   }

   struct mem_data *data = NULL;
   data = (struct mem_data *)malloc(SIZEOF_BUFFER_DATA_STRUCT);
   if (data == NULL) {
      printf("Error: Memory allocation failed\n");
      exit(1);
   }
   
   data = (struct mem_data *)ptr;
   close(fd);

   return *data;
}