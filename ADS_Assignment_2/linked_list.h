/*-----------------------------------------------------------------------------
* Project: Assignment 2
* linked_list.h :
*        = the interface of the module 'linked_list' of the project
* This module handles all functions (creation, insertion, searching & freeing)
* relating to the linked list structure within the program
* Created by Rebecca Chao (rcchao@student.unimelb.edu.au)
* 5/09/2024
-----------------------------------------------------------------------------*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct {
	int recordID; 
	int suburbID;
	char* suburb_name; 
	int year_recorded;
	char* state_IDs;
	char* state_names;
	char* gov_IDs;
	char* gov_names;
	double latitude;
	double longitude;
} suburb_data;

typedef struct node {
    char* key;
    suburb_data *value;
    struct node *next;
} node_t;

typedef struct list {
    node_t *head;
    node_t *tail;
} list_t;

// Create & insert into linked list >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// Creates & returns an empty linked list
// based on listCreate function from COMP20003 Workshop 3.4
list_t *list_create();

// Inserts a new node with value "value" to the end of "list" 
void list_append(list_t *list, suburb_data *value);

// Insert suburb_data into a linked list node by first casting void** pointer
void insert_to_list(suburb_data* suburb, void** structure);

// Searching linked list >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// Loops through the 2d array to find and search suburbs
void search_and_print(list_t *dict, FILE* out_file, char **suburbs);

// Taken from scaffold answer of assignment 1:
// Compare data with a key, counts character comparisons
int dataKeyCmp(void *vdata, void *key, int *comps);

// Performs linear search on list, and prints it to terminal & stdout
void linear_search(list_t *dict, FILE* out_file, char *suburb);

// Freeing linked list >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// Traverse through and free the linked list
void free_llist(list_t *llist);

#endif 
