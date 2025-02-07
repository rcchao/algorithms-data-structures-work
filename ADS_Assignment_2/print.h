/*-----------------------------------------------------------------------------
* Project: Assignment 2
* print.h :  
*        = the implementation of the interface 'print' of the project
* This module prints results to stdout and the outfile for both stages of the
* project
* Created by Rebecca Chao (rcchao@student.unimelb.edu.au)
* 5/09/2024
-----------------------------------------------------------------------------*/

#ifndef _PRINT_H_
#define _PRINT_H_

#include "linked_list.h"

// Find and print found suburb to outfile with specified format
void stdout_print(int counter, char* suburb, int bits, int nodes_accessed, int strcmps);

// Find and print suburb to outfile with specified format
void outfile_print(FILE* out_file, suburb_data* value);

#endif
