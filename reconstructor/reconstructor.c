#include <stdio.h>
#include <stdbool.h> 

char get_char_from_struct(void);
void write(char ch);
bool is_finished(void);
int get_current_char_counter(void);
void write_counter_mem(int current_char_counter);
void update_write_flag_to_true(void);
int get_file_length(void);

int main()
{
    bool finished_flag = is_finished();
    char character = get_char_from_struct();
    if (!finished_flag){
        write(character);
    }
    return 0;
}

char get_char_from_struct(void)
{
    char temp = 'a';
    return temp;
}

int get_current_char_counter(void){
    // TODO: Get count of characters
    return 2;
}

int get_file_length(void){
    // TODO: Get total of characters in file
    return 9;
}

void write_counter_mem(int current_char_counter){
    // TODO: Write write counter in mem
    printf("The number is: %d\n", current_char_counter);
}

void update_write_flag_to_true(void){
    // TODO: Write read flag to true to indicate writing is finished 
    printf("True");
}

bool is_finished(void){
    int current_counter = get_current_char_counter();
    int file_length = get_file_length();

    if (current_counter == file_length) {
        update_write_flag_to_true();
        return true;
    }
    else{
        current_counter ++;
        write_counter_mem(current_counter);
        return false;
    }
}

void write(char ch)
{
    // Open file in write mode
    FILE* copyFile = fopen("copy.txt", "a");

    if (copyFile == NULL) {
        printf("Error opening file.\n");
        return; // Exit function if file opening fails
    }

    // Write character to file
    fputc(ch, copyFile);

    // Close file
    fclose(copyFile);
    printf("File copied successfully.\n");
}
