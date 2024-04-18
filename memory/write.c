#include "write.h"


void write_to_buffer(char ch, int buffer_index)
{
   int fd;
   char *ptr;

   struct buffer_data data;
   data.character = ch;
   
   // Get current date
   time_t current_time = time(NULL);
   char date_string[sizeof(data.date)];
   strftime(date_string, sizeof(data.date), "%Y-%m-%d", localtime(&current_time));
   strncpy(data.date, date_string, sizeof(data.date));
   data.date[sizeof(data.date) - 1] = '\0'; // Ensure null-termination

   // Get current time
   char time_string[sizeof(data.time)];
   strftime(time_string, sizeof(data.time), "%H:%M:%S", localtime(&current_time));
   strncpy(data.time, time_string, sizeof(data.time));
   data.time[sizeof(data.time) - 1] = '\0'; // Ensure null-termination
   
   fd = shm_open (SMOBJ_NAME_MEM_CHARS,  O_RDWR  , 00200); /* open s.m object*/
   if(fd == -1)
   {
      printf("Error file descriptor %s\n", strerror(errno));
	   exit(1);
   }
   
   ptr = mmap(NULL, SIZEOF_BUFFER_DATA_STRUCT*100, PROT_WRITE, MAP_SHARED, fd, 0);
   if(ptr == MAP_FAILED)
   {
      printf("Map failed in write process: %s\n", strerror(errno));
      exit(1);
   }
   
   char *data_ptr= (char*)&data;
   char *address = ptr + (buffer_index * SIZEOF_BUFFER_DATA_STRUCT);
   memmove(address, data_ptr, sizeof(data));
   printf("Char: %c, Date: %s, Time: %s, Address: %d\n", data.character, data.date, data.time, &address);
   close(fd);
}

void write_to_stats(struct stats_data stats)
{
   int fd;
   char *ptr;

   fd = shm_open (SMOBJ_NAME_MEM_STATS,  O_RDWR  , 00200); /* open s.m object*/
   if(fd == -1)
   {
      printf("Error file descriptor %s\n", strerror(errno));
	   exit(1);
   }
   
   ptr = mmap(NULL, SIZEOF_SMOBJ_MEM_STATS, PROT_WRITE, MAP_SHARED, fd, 0);
   if(ptr == MAP_FAILED)
   {
      printf("Map failed in write process: %s\n", strerror(errno));
      exit(1);
   }
   
   char *data_ptr= (char*)&stats;
   memmove(ptr, data_ptr, SIZEOF_SMOBJ_MEM_STATS);
   close(fd);
}

void write_to_memdata(struct mem_data mem)
{
   int fd;
   char *ptr;

   fd = shm_open (SMOBJ_NAME_MEM_DATA,  O_RDWR  , 00200); /* open s.m object*/
   if(fd == -1)
   {
      printf("Error file descriptor %s\n", strerror(errno));
	   exit(1);
   }
   
   ptr = mmap(NULL, SIZEOF_SMOBJ_MEM_DATA, PROT_WRITE, MAP_SHARED, fd, 0);
   if(ptr == MAP_FAILED)
   {
      printf("Map failed in write process: %s\n", strerror(errno));
      exit(1);
   }
   
   char *data_ptr= (char*)&mem;
   memmove(ptr, data_ptr, SIZEOF_SMOBJ_MEM_STATS);
   close(fd);
}