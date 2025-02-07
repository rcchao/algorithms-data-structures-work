/*-----------------------------------------------------------------------------
* Project: Assignment 2
* ptree.h :
*        = the interface of the module 'ptree' of the project
* This module handles all functions (creation, insertion, searching & freeing)
* relating to the patricia tree structure within the program
* Created by Rebecca Chao (rcchao@student.unimelb.edu.au)
* 5/09/2024
-----------------------------------------------------------------------------*/

#ifndef _PTREE_H_
#define _PTREE_H_

#include <stdio.h>
#include <stdlib.h>
#include "data.h"

typedef struct prefix_node prefix_node_t;

typedef struct prefix_node{
    int prefix_bits;          // Number of bits in the prefix
    char* stem;               // The bit sequence of the prefix
    prefix_node_t* branch_0;  // Pointer to the branch starting with bit "0"
    prefix_node_t* branch_1;  // Pointer to the branch starting with bit "0"
    list_t* results;          // Linked list of results
} prefix_node_t;

// Create & insert into patricia tree >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// Insert suburb_data into a patricia tree node by first casting void** pointer
void insert_to_ptree(suburb_data* suburb, void** structure);

// Creates & returns a new Patricia tree node
prefix_node_t* create_node(int prefix_bits, char* stem);

// Initialises the Patricia tree root node
prefix_node_t* init_ptree(suburb_data *value);

// Recursive function which adds a Patricia tree node to an existing tree
void insert_ptree_node(prefix_node_t* node, suburb_data* suburb,
                       int bits_searched);

// Find the first mismatched bit between the current node's stem and the key
// Note that at maximum, this only checks for the length of the stem node
int find_mismatch_bit(char *stem, char *inserted_key, int prefix_bits,
                      int bits_searched);

// Searching patricia tree >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// Search and return the list of results for a singular query
// Prints to stdout
void search_ptree(prefix_node_t* root, char *search_string, FILE* out_file);

// Perform an in-order DFS on the nodes past the current one to find node with
// minimum edit distance
void inorder_traversal(prefix_node_t* root, char* search_string, int* min_dist,
                       prefix_node_t** min_node);

// Freeing patricia tree >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// Free the patricia tree using postorder traversal
void free_ptree(prefix_node_t* root);

// Helper Functions taken from spec >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// Allocates new memory to hold the numBits specified and fills the allocated
// memory with the numBits specified starting from the startBit of the oldKey
// array of bytes
char *create_stem(char *oldKey, unsigned int startBit, unsigned int numBits);

// Helper function. Gets the bit at bitIndex from the string s
int get_bit(char *s, unsigned int bitIndex);

// Returns min of 3 integers 
// reference: https://www.geeksforgeeks.org/edit-distance-in-c/
int min(int a, int b, int c);

// Returns the edit distance of two strings
// reference: https://www.geeksforgeeks.org/edit-distance-in-c/
int edit_dist(char *str1, char *str2, int n, int m);

#endif
