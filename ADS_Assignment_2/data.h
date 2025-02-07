/*-----------------------------------------------------------------------------
* Project: Assignment 2
* data.h :
*        = the interface of the module 'data' of the project
* This data agnostic module processes a CSV of known format into the input
* structure (linked list or a patricia tree)
* Created by Rebecca Chao (rcchao@student.unimelb.edu.au)
* 5/09/2024
-----------------------------------------------------------------------------*/
#ifndef _DATA_H_
#define _DATA_H_

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

// Processes the input dataset into the input structure (list_t* or prefix_node_t*)
void* process_file_content(FILE *file, void (*insert_func)(suburb_data*, void**), void** structure);

// Parses one line of input data and stores it in the input structure (list_t* or prefix_node_t*)
void parse_line(char* line, ssize_t line_len, void (*insert_func)(suburb_data*, void**), void** structure);

// Store one field into suburb_data
void process_field(suburb_data *suburb, int field, const char *tmp);

// Freeing suburb_data struct >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// Frees a suburb_data structure
void suburb_free(suburb_data *value);

#endif


