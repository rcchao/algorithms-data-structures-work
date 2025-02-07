/*-----------------------------------------------------------------------------
* Project: Assignment 1
* search.h :  
*        = the interface of the module 'search' of the project
* Created by Amy Sun (axsun@student.unimelb.edu.au)
* and Rebecca Chao (rcchao@student.unimelb.edu.au)
* 15/08/2024
-----------------------------------------------------------------------------*/
#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "process.h"

// Loops through the 2d array to find and search suburbs
void search_and_print(list_t *dict, FILE* out_file, char **suburbs);

// Performs linear search on list, and prints it to terminal & stdout
void linear_search(list_t *dict, FILE* out_file, char *suburb);

// Find and print suburb to outfile with specified format
void outfile_print(FILE* out_file, suburb_data* value);

#endif
