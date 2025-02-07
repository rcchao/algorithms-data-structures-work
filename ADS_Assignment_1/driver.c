/*-----------------------------------------------------------------------------
* Project: Assignment 1
* driver.c : 
*            = the main program of the project 
* Created by Amy Sun (axsun@student.unimelb.edu.au)
* and Rebecca Chao (rcchao@student.unimelb.edu.au)
* 15/08/2024

* Creates a dictionary based on a linked list, containing information about
* Australian suburbs from a dataset.
* With input by the user, two operations can be performed on the dictionary:
* (Stage 1) Searching
*           Which looks for a key in a list, outputting any records that match
* (Stage 2) Deletion
*           Which removes all records associated with a set of keys and
*           outputs the remaining records
*
* To run stage 1 of the program type: 
* ./dict1 1 inputfile.csv outputfile.csv
* Begin typing suburb names to search for, ^D or double return to stop
*
* To run stage 2 of the program type: 
* ./dict2 2 inputfile.csv outputfile.csv
* Begin typing suburb names to delete, ^D or double return to stop
-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"
#include "search.h"
#include "free.h"
#include "delete.h"

#define STAGE_1 "1" 
#define STAGE_2 "2"
#define NUM_ARGS 4

int main(int argc, char *argv[]) {
    // Checking that 4 command line arguments are input 
    if(argc != NUM_ARGS){
        return EXIT_FAILURE;}

    FILE *in_file = fopen(argv[2], "r");
    FILE *out_file = fopen(argv[3], "w");

    // Check that both files could be opened
    if ((!in_file) || (!out_file)) {
        return EXIT_FAILURE;
    }

    // STAGE 0: Process
    list_t* dict;
    dict = process_file_content(in_file);
    fclose(in_file);
    char** user_input = all_suburbs();

    // STAGE 1: Search
    if (strcmp(argv[1],STAGE_1) == 0) {
        search_and_print(dict, out_file, user_input);
    }

    // STAGE 2: Deletion
    if (strcmp(argv[1],STAGE_2) == 0) {
        delete_all_nodes(dict, user_input);
        print_remaining(dict, out_file);
    }

    // STAGE 3: Free
    free_2d_array(user_input);
    free_dict(dict);
    fclose(out_file);
    return EXIT_SUCCESS;
}
