/*-----------------------------------------------------------------------------
* Project: Assignment 1
* free.c :  
*        = the implementation of the module 'free' of the project
* Created by Amy Sun (axsun@student.unimelb.edu.au)
* and Rebecca Chao (rcchao@student.unimelb.edu.au)
* 15/08/2024
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "free.h"
#include "process.h"

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

// Free the entire dictionary by traversing through the linked list
void free_dict(list_t *dict){
    // Ensure that we do not attempt to free a NULL
    assert(dict != NULL);
    node_t *curr = dict->head;

    // Iterate through the dict, freeing each node
    while (curr) {
        node_t *tmp = curr;
        curr = curr->next;
        // frees suburb_data of prev. node
        suburb_free(tmp->value); 
        tmp->value = NULL;
        free(tmp);
        tmp = NULL;
	}
    // Free the list itself
	free(dict);
	dict = NULL;
}

// Frees a suburb_data structure
void suburb_free(suburb_data *value) {
	free(value->suburb_name);
	value->suburb_name = NULL;
	free(value->state_IDs);
	value->state_IDs = NULL;
	free(value->state_names);
	value->state_names = NULL;
	free(value->gov_IDs);
	value->gov_IDs = NULL;
	free(value->gov_names);
	value->gov_names = NULL;
	free(value);
	value = NULL;
};
