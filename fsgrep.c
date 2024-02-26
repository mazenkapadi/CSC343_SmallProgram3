/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/main.c to edit this template
 */

/* 
 * File:   main.c
 * Author: mazenkapadi
 *
 * Created on February 21, 2024, 12:29 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

// Function to search for a search term in a file

void fsgrep(const char *search_term, FILE *file) {
    char *line = NULL; // Pointer to dynamically allocated memory for the line
    size_t len = 0; // The length of the line - because in the world of code, even lines have dimensions
    ssize_t read; // The number of characters read by getline() - basically, the line's way of saying "howdy"

    // Read each line from the file
    while ((read = getline(&line, &len, file)) != -1) {
        // Is the search term hiding within this line?
        if (strstr(line, search_term) != NULL) {
            // Aha! We've found it - printing the line like a proud discoverer
            printf("%s", line);
        }
    }

    free(line); // Setting the line free, like a bird released from its cage, to roam the wild plains of memory once again


}

int main(int argc, char *argv[]) {
    // Ensure the correct number of command-line arguments is provided
    if (argc < 2) {
        // Inform the user of the correct usage if the search term is missing
        fprintf(stderr, "Usage: %s searchterm [file ...]\n", argv[0]);
        // Return a non-zero exit status to indicate incorrect usage
        return 1;
    }

    // Extract the search term from the command line arguments
    const char *search_term = argv[1];

    // Check if only the search term is provided without any files
    if (argc == 2) {
        // Read from standard input
        fsgrep(search_term, stdin);
    } else {
        // Read from files
        for (int i = 2; i < argc; i++) {
            // Open each file provided in the command line arguments
            FILE *file = fopen(argv[i], "r");
            // Check if the file is successfully opened
            if (file == NULL) {
                // Print error message if the file cannot be opened
                fprintf(stderr, "fsgrep: cannot open file %s\n", argv[i]);
                return 1;
            }
            // Search for the search term in the file
            fsgrep(search_term, file);
            // Close the file
            fclose(file);
        }
    }

    // Huzzah! We've sailed the seven seas, fought valiantly, and returned triumphant - until the next adventure beckons
    return 0;
}