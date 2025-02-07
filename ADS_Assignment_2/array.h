/*-----------------------------------------------------------------------------
* Project: Assignment 2
* array.h :
*        = the interface of the module 'array' of the project
* This module handles the user's input into the command line using a 2d
* dynamically allocated array
* Created by Rebecca Chao (rcchao@student.unimelb.edu.au)
* 5/09/2024
-----------------------------------------------------------------------------*/

// Reads in user input for one suburb string, stores it dynamically 
// and returns the pointer
char* get_string();

// Put together and returns s 2d array that has the user input suburbs
char** all_suburbs();

// Freeing 2d array >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// Free the 2d array of suburbs input by the user
void free_2d_array(char **suburb);
