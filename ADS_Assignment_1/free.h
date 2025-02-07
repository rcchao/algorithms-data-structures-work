/*-----------------------------------------------------------------------------
* Project: Assignment 1
* free.c :  
*        = the interface of the module 'free' of the project
* Created by Amy Sun (axsun@student.unimelb.edu.au)
* and Rebecca Chao (rcchao@student.unimelb.edu.au)
* 15/08/2024
-----------------------------------------------------------------------------*/

#ifndef _FREE_H_
#define _FREE_H_
#include "process.h"

// Free the 2d array of suburbs input by the user
void free_2d_array(char **suburb);

// Free the entire dictionary by traversing through the linked list
void free_dict(list_t *dict);

// Frees a suburb_data structure
void suburb_free(suburb_data *value);

#endif
