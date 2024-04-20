#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    
    // Loop infinitely to read new data added to the file
    while (1) {
        const char *filename = argv[1];
        FILE *file = fopen(filename, "r");

        if (file == NULL) {
            perror("Failed to open file");
            exit(EXIT_FAILURE);
        }

        // Seek to the end of the file initially
        fseek(file, 0, SEEK_SET);

        int c;

        // Read a character if available
        while ((c = fgetc(file)) != EOF) {
            putchar(c);  // Output the character
        }

        // Flush stdout to ensure all output is printed to the console
        fflush(stdout);

        // Check for new data every 1 second
        sleep(1);

        // Clear the EOF indicator and try reading again
        clearerr(file);
        system("clear");
        
        fclose(file);
    }

    
    return 0;
}
