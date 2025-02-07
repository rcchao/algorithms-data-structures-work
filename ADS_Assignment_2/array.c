/*-----------------------------------------------------------------------------
* Project: Assignment 2
* array.c :
*        = the implementation of the module 'array' of the project
* This module handles the user's input into the command line using a 2d
* dynamically allocated array
* Created by Rebecca Chao (rcchao@student.unimelb.edu.au)
* 5/09/2024
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define DYNAMIC 2

// Reads in user input for one suburb string, stores it dynamically 
// and returns the pointer
char* get_string() {
    char c;
    size_t len = 0, current_size = DYNAMIC;
    char *suburb = (char*) calloc(current_size, sizeof(char));
    assert(suburb);

    while ((c = getchar()) != EOF && c != '\n') {
        suburb[len++] = c;
        if (len == current_size) {
            size_t old_size = current_size;
            current_size *= DYNAMIC;
            suburb = realloc(suburb, current_size * sizeof(char));
            assert(suburb);
            // Recalloc
            int size_diff = (current_size - old_size) * sizeof(char);
            memset(suburb + old_size, 0, size_diff);
        }
    }
    return suburb;
}

// Put together and returns a 2d array that has the user input suburbs
char** all_suburbs() {
    size_t max_size = DYNAMIC;
    size_t num_strings = 0;
    char **suburbs = (char**) calloc(max_size, sizeof(char*));
    assert(suburbs);

    while (1) {
        char *word = get_string();
        // End of input when an empty string is returned
        if (strlen(word) == 0) { 
            free(word);
            break;
        }
        suburbs[num_strings++] = word;
        if (num_strings == max_size) {
            max_size *= DYNAMIC;
            suburbs = realloc(suburbs, max_size * sizeof(char*));
            assert(suburbs);
        }
    }
    memset(suburbs + num_strings, 0, (max_size - num_strings) * sizeof(char*));
    assert(suburbs);
    return suburbs;
}

// Freeing 2d array >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// Free the 2d array of suburbs input by the user
void free_2d_array(char **suburbs) {
    if (suburbs == NULL) {
        return;
    }
    for (size_t i = 0; suburbs[i] != NULL; i++) {
        // Free each individual string
        free(suburbs[i]);
        suburbs[i] = NULL;
    }
    // Free the array of pointers
    free(suburbs);
    suburbs = NULL;
}
