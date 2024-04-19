#include "write.h"


void write_to_buffer(char ch, int buffer_index, char* ptr)
{
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
   
   char *data_ptr= (char*)&data;
   char *address = ptr + (buffer_index * SIZEOF_BUFFER_DATA_STRUCT);

   memmove(address, data_ptr, sizeof(data));

   printf("Char: %c, Date: %s, Time: %s, Buffer Index: %d\n", data.character, data.date, data.time, buffer_index);
}

void write_to_stats(struct stats_data stats, char* ptr)
{
   char *data_ptr= (char*)&stats;
   memmove(ptr, data_ptr, SIZEOF_SMOBJ_MEM_STATS);
}

void write_to_mem_data(struct mem_data mem, char* ptr)
{
   char *data_ptr= (char*)&mem;
   memmove(ptr, data_ptr, SIZEOF_SMOBJ_MEM_DATA);
}