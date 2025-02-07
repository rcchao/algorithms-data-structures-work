/*-----------------------------------------------------------------------------
* Project: Assignment 2
* linked_list.c :
*        = the implementation of the module 'linked_list' of the project
* This module handles all functions (creation, insertion, searching & freeing)
* relating to the linked list structure within the program
* Created by Rebecca Chao (rcchao@student.unimelb.edu.au)
* 5/09/2024
-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "linked_list.h"
#include "data.h"
#include "print.h"

#define BITS_PER_BYTE 8

// Create & insert into linked list >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// Creates & returns an empty linked list
// based on listCreate function from COMP20003 Workshop 3.4
list_t* list_create() {
	list_t *list = malloc(sizeof(*list));
	assert(list);
	list->head = list->tail = NULL;
	return list;
}

// Inserts a new node with value "value" to the end of "list" 
void list_append(list_t *list, suburb_data *value) {
	assert(list);

    // Retrieve the key from suburb_data
    char* key = value->suburb_name;

	// Creates a new node and set data 
	node_t *new = malloc(sizeof(*new));
	assert(new);
    new->key = key;
	new->value = value;
	new->next = NULL;

	// If the list is empty, set the head and tail to the new node
	if (list->tail == NULL) {
		list-> head = new;
		list-> tail = new;
	} else {
		// Link the node to the chain & update tail
		list->tail->next = new;
		list->tail = new;
	}
}

// Insert suburb_data into a linked list by first casting void** pointer
void insert_to_list(suburb_data* suburb, void** structure) {
    // Cast the structure to list_t**
    list_t** dict = (list_t**) structure;
    // Append the suburb to the list
    list_append(*dict, suburb);
}

// Searching linked list >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// Loops through the 2d array to find and search suburbs
void search_and_print(list_t *dict, FILE* out_file, char **suburbs) {
    for (size_t i = 0; suburbs[i] != NULL; i++) {
    linear_search(dict, out_file, suburbs[i]);
    }
}

// Taken from scaffold answer of assignment 1:
// Compare data with a key, counts character comparisons
int dataKeyCmp(void *vdata, void *key, int *comps) {
  node_t *data = vdata;
  char *s1 = data->key, *s2 = key;
  int n1 = strlen(s1), n2 = strlen(s2);

  if (comps == NULL) {
    return strcmp(s1, s2);
  }

  int i = 0;
  // <= to include nullbyte
  while (i <= n1 && i <= n2) {
    (*comps)++;
    if (s1[i] > s2[i]) {
      return 1;
    }
    else if (s1[i] < s2[i]) {
      return -1;
    }
    i++;
  }
  return 0;
}

// Performs linear search on list, and prints suburb info to stdout & outfile
void linear_search(list_t *dict, FILE* out_file, char *suburb) {
    int counter = 0;
    int bytes = 0;
    int strcmps = 0;
    int nodes_accessed = 0;
    fprintf(out_file, "%s -->\n", suburb); 

    // Iterate through the dictionary to find key "suburb" & its frequency
    node_t *curr = dict->head;
    while (curr != NULL) {
        nodes_accessed++;
        suburb_data *value = curr->value;
        strcmps++;
        if (dataKeyCmp(curr, suburb, &bytes) == 0) {
            // Found the suburb, print to outfile & and update frequency
            counter++;
            outfile_print(out_file, value);
        }
        struct node *nextNode = curr->next;
        curr = nextNode;
    }

    // Print suburb info to stdout:
    stdout_print(counter, suburb, (bytes * BITS_PER_BYTE),
                                  nodes_accessed, strcmps);

    return;
}

// Freeing linked list >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void free_llist(list_t *llist){
    // Ensure that we do not attempt to free a NULL
    assert(llist != NULL);
    node_t *curr = llist->head;

    // Iterate through the llist, freeing each node
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
	free(llist);
	llist = NULL;
}
