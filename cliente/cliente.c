#include <stdio.h>

int main()
{
    int char_pos = get_char_pos();
    read_char(char_pos);
    return 0;
}

int get_char_pos(){
    return 9;
}

void write_char_pos_mem(int current_char_pos){
    printf("The number is: %d\n", current_char_pos);
}

void update_read_flag_to_true(){
    printf("True");
}


int read_char(int char_pos){
    const char* filename = "readme.txt";
    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return 1;
    }

    char_pos++;

    // Move the file pointer to char_pos character
    if (fseek(fp, char_pos, SEEK_SET) != 0) {
        printf("Error: fseek failed\n");
        fclose(fp);
        return 1;
    }

    // Read the character at the current file position
    int ch = fgetc(fp);
    if (ch == EOF) {
        printf("Error: End of file reached\n");
        update_read_flag_to_true();
        fclose(fp);
        return 1;
    }

    write_char_pos_mem(char_pos);
    
    printf("The character in the file is: %c\n", (char)ch);

    // Close the file
    fclose(fp);

    return 0;
}