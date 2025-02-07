/*-----------------------------------------------------------------------------
* Project: Assignment 1
* delete.c :
*        = the interface of the module 'delete' of the project
* Created by Amy Sun (axsun@student.unimelb.edu.au)
* and Rebecca Chao (rcchao@student.unimelb.edu.au)
* 15/08/2024
-----------------------------------------------------------------------------*/
#ifndef _DELETE_H_
#define _DELETE_H_

// Loops through the 2d array to find and delete suburbs
void delete_all_nodes(list_t *dict, char **suburbs);

// Performs linear search on list, and prints deleted suburb info
// to stdout & outfile
void delete_node(list_t *list, char *key);

// Prints deleted suburb info to stdout
void print_delete_stdout(int counter, char* suburb);

// Prints the remaining dict contents to outfile after deletion
void print_remaining(list_t *dict, FILE* out_file);

// Inserts double quotes around fields which contain commas
void insert_dbl(FILE* out_file, char* string);

#endif
