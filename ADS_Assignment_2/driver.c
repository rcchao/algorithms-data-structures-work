/*-----------------------------------------------------------------------------
* Project: Assignment 2
* driver.c : 
*            = the main program of the project 
* Created by Rebecca Chao (rcchao@student.unimelb.edu.au)
* 5/09/2024

* Creates a dictionary based on a linked list, containing information about
* Australian suburbs from a dataset.
* With input by the user, two operations can be performed on the dictionary:
* (Stage 3) Searching using a linked list
*           Which looks for a key in a list, outputting any records that match
* (Stage 4) Searching with spellcheck using a Patricia tree
*           Which looks for a key in a list, outputting records that match
*           fully and finding similar records for keys that do not match
*
* To run stage 3 of the program type: 
* ./dict3 3 inputfile.csv outputfile.csv
* Begin typing suburb names to search for, ^D or double return to stop
*
* To run stage 4 of the program type: 
* ./dict4 4 inputfile.csv outputfile.csv
* Begin typing suburb names to search for, ^D or double return to stop
-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"
#include "data.h"
#include "linked_list.h"
#include "ptree.h"

#define STAGE_3 "3"
#define STAGE_4 "4"
#define NUM_ARGS 4

int main(int argc, char *argv[]) {
    // Checking that 4 command line arguments are input 
    if(argc != NUM_ARGS){
        printf("Wrong num of args\n");
        return EXIT_FAILURE;
    }

    FILE *in_file = fopen(argv[2], "r");
    FILE *out_file = fopen(argv[3], "w");

    // Check that both files could be opened
    if ((!in_file) || (!out_file)) {
        printf("One or both files couldn't be opened\n");
        return EXIT_FAILURE;
    }
    
    // Process the user's command line input
    char** user_input = all_suburbs();

    // STAGE 3: Linked list approach, no autocomplete
    if (strcmp(argv[1],STAGE_3) == 0) {
        // Create the linked list dictionary
        list_t* list_dict = list_create();
        list_dict = (list_t*) process_file_content(in_file,
                                                    insert_to_list,
                                                    (void**)&list_dict);
        fclose(in_file);

        // Perform search
        search_and_print(list_dict, out_file, user_input);

        // Free linked list dictionary
        free_llist(list_dict);
    }

    // STAGE 4: Patricia tree approach, no autocomplete
    if (strcmp(argv[1],STAGE_4) == 0) {
        // Create and pass the root pointer to process_file_content
        // Note '&' used due to root being changed later
        prefix_node_t* root = NULL;
        root = (prefix_node_t*) process_file_content(in_file,
                                                    insert_to_ptree,
                                                    (void**)&root);
        fclose(in_file);

        // Perform search
        for (size_t i = 0; user_input[i]!= NULL; i++) {
            search_ptree(root, user_input[i], out_file);
        }

        // Free Patricia tree
        free_ptree(root);
    }
    

    // Free user's command line input and close output file
    free_2d_array(user_input);
    fclose(out_file);
    return EXIT_SUCCESS;
}
