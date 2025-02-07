/*-----------------------------------------------------------------------------
* Project: Assignment 1
* search.c :  
*        = the implementation of the module 'search' of the project
* Created by Amy Sun (axsun@student.unimelb.edu.au)
* and Rebecca Chao (rcchao@student.unimelb.edu.au)
* 15/08/2024
-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "search.h"
#include "process.h"

#define FORMAT_STRING "COMP20003 Code: %d, Official Code Suburb: %d, "\
       "Official Name Suburb: %s, Year: %d, Official Code State: %s, "\
       "Official Name State: %s, Official Code Local Government Area: %s, "\
       "Official Name Local Government Area: %s, Latitude: %.7lf, "\
       "Longitude: %.7lf\n"

// Loops through the 2d array to find and search suburbs
void search_and_print(list_t *dict, FILE* out_file, char **suburbs) {
    for (size_t i = 0; suburbs[i] != NULL; i++) {
    linear_search(dict, out_file, suburbs[i]);
    }
}

// Performs linear search on list, and prints suburb info to stdout & outfile
void linear_search(list_t *dict, FILE* out_file, char *suburb) {
    int counter = 0;
    fprintf(out_file, "%s -->\n", suburb); 

    // Iterate through the dictionary to find key "suburb" & its frequency
    node_t *curr = dict->head;
    while (curr != NULL) {
        suburb_data *value = curr->value;
        if (strcmp(curr->key,suburb) == 0) {
            // Found the suburb, print to outfile & and update frequency
            counter++;
            outfile_print(out_file, value);
        }
    struct node *nextNode = curr->next;
    curr = nextNode;
    }

    // Print suburb info to stdout:
    if (counter == 0) {
        printf("%s --> NOTFOUND\n", suburb);
    } else {
    printf("%s --> %d records found\n", suburb, counter);
    }
    return;
}

// Find and print suburb to outfile with specified format
void outfile_print(FILE *out_file, suburb_data *value) {
    fprintf(out_file, FORMAT_STRING, value->recordID, value->suburbID,
            value->suburb_name, value->year_recorded, value->state_IDs,
            value->state_names, value->gov_IDs, value->gov_names, 
            value->latitude, value->longitude);
    return;
}

