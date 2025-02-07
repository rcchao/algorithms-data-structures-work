/*-----------------------------------------------------------------------------
* Project: Assignment 1
* delete.c :
*        = the implementation of the module 'delete' of the project
* Created by Amy Sun (axsun@student.unimelb.edu.au)
* and Rebecca Chao (rcchao@student.unimelb.edu.au)
* 15/08/2024
-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "process.h"
#include "free.h"
#include "delete.h"

#define COMMA ','
#define HEADER "COMP20003 Code,Official Code Suburb,Official Name Suburb,Year,\
Official Code State,Official Name State,Official Code Local Government Area,\
Official Name Local Government Area,Latitude,Longitude"

// Loops through the 2d array to find and delete suburbs
void delete_all_nodes(list_t *dict, char **suburbs) {
    for (size_t i = 0; suburbs[i] != NULL; i++) {
        delete_node(dict, suburbs[i]);
    }
  
}

// Performs linear search on list, and prints deleted suburb info
// to stdout & outfile
void delete_node(list_t *dict, char *key) {
    // Either dict or key are null, return early
    if (dict == NULL || key == NULL) {
        return;
    }

    node_t *current = dict->head;
    node_t *previous = NULL;
    int counter = 0;

    // Traverse the dict to find the node to delete
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            // Node to delete found
            counter++;
            if (previous == NULL) {
                // Deleting the head node
                dict->head = current->next;
                if (dict->head == NULL) {
                    // dict is now empty
                    dict->tail = NULL;
                }
            } else {
                // Deleting a non-head node
                previous->next = current->next;
                if (previous->next == NULL) {
                    // Update the tail if last node is deleted
                    dict->tail = previous;
                }
            }
            // Free the current node
            suburb_free(current->value);
            node_t *temp = current;
            current = current->next;
            free(temp);
        }
        else {
            // Move to the next node
            previous = current;
            current = current->next;
        }
    }
    print_delete_stdout(counter, key);
}

// Prints deleted suburb info to stdout
void print_delete_stdout(int counter, char *suburb) {
    // Output to stdout:
    if (counter == 0) {
        printf("%s --> NOTFOUND\n", suburb);
    } else {
    printf("%s --> %d records deleted\n", suburb, counter);
    }
    return;
}


// Prints the remaining dict contents to outfile after deletion
void print_remaining(list_t *dict, FILE* out_file) {
    fprintf(out_file, "%s\n",HEADER);

    // Traverse through dict and print each suburb
    node_t *current = dict->head;
    while (current) {
        fprintf(out_file, "%d,",current->value->recordID);
        fprintf(out_file, "%d,",current->value->suburbID);
        insert_dbl(out_file, current->value->suburb_name);
        fprintf(out_file, "%d,",current->value->year_recorded);
        insert_dbl(out_file, current->value->state_IDs);
        insert_dbl(out_file, current->value->state_names);
        insert_dbl(out_file, current->value->gov_IDs);
        insert_dbl(out_file, current->value->gov_names);
        fprintf(out_file, "%.7lf,",current->value->latitude);
        fprintf(out_file, "%.7lf\n",current->value->longitude);
        current = current->next;
    }
    return; 
}

// Inserts double quotes around fields which contain commas
void insert_dbl(FILE* out_file, char* string){
    int index = 0;
    int comma = 0;
    while (string[index]) {
        if (string[index] == COMMA) {
            comma = 1;
            break;
        }
        index++;
    }

    // If a comma is present, insert double quotes around the field
    if (comma){
        fprintf(out_file, "\"%s\",", string);
    }
    else {
        fprintf(out_file, "%s,",string);
    }
    return;
}


