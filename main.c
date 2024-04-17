#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "./creador/creador.h"

int main(){
    struct buffer_data data;
    data.character = 'a';
    
    // Get current date
    time_t current_time = time(NULL);
    char date_string[sizeof(data.date)];
    strftime(date_string, sizeof(data.date), "%Y-%m-%d", localtime(&current_time));
    strncpy(data.date, date_string, sizeof(data.date));
    data.date[sizeof(data.date) - 1] = '\0'; // Ensure null-termination
    printf("The current date is: %s\n", data.date);


    // Get current time
    char time_string[sizeof(data.time)];
    strftime(time_string, sizeof(data.time), "%H:%M:%S", localtime(&current_time));
    strncpy(data.time, time_string, sizeof(data.time));
    data.time[sizeof(data.time) - 1] = '\0'; // Ensure null-termination
    printf("The current time is: %s\n", data.time);
    return 0;
}