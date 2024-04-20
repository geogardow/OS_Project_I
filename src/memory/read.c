#include "read.h"

struct buffer_data* read_from_buffer(int buffer_index, char* ptr)
{
   char *address = ptr + (buffer_index * SIZEOF_BUFFER_DATA_STRUCT);

   struct buffer_data *data = NULL;
   data = (struct buffer_data *)malloc(SIZEOF_BUFFER_DATA_STRUCT);
   if (data == NULL) {
      printf("Error: Memory allocation failed\n");
      exit(1);
   }
   
   data = (struct buffer_data *)address;
   printf("Char: %c, Date: %s, Time: %s, Buffer Index: %d\n", data->character, data->date, data->time, buffer_index);
   return data;
}

struct stats_data read_from_stats(char* ptr)
{
   struct stats_data *data = NULL;
   data = (struct stats_data *)malloc(SIZEOF_SMOBJ_MEM_STATS);
   if (data == NULL) {
      printf("Error: Memory allocation failed\n");
      exit(1);
   }
   
   data = (struct stats_data *)ptr;

   return *data;
}

struct mem_data read_from_mem_data(char* ptr)
{
   struct mem_data *data = NULL;
   data = (struct mem_data *)malloc(SIZEOF_SMOBJ_MEM_DATA);
   if (data == NULL) {
      printf("Error: Memory allocation failed\n");
      exit(1);
   }
   
   data = (struct mem_data *)ptr;

   return *data;
}