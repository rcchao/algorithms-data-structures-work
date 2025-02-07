/*-----------------------------------------------------------------------------
* Project: Assignment 2
* ptree.c :
*        = the implementation of the module 'ptree' of the project
* This module handles all functions (creation, insertion, searching & freeing)
* relating to the patricia tree structure within the program
* Created by Rebecca Chao (rcchao@student.unimelb.edu.au)
* 5/09/2024
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "ptree.h"
#include "linked_list.h"
#include "data.h"
#include "print.h"

#define BITS_PER_BYTE 8
#define NO_MISMATCH_BIT -1
#define PLACEHOLDER_MAX 9999

// Create & insert into patricia tree >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// Creates a new prefix node 
prefix_node_t* create_node(int prefix_bits, char* stem) {
    prefix_node_t* newNode = (prefix_node_t*)malloc(sizeof(prefix_node_t));
    assert(newNode);
    newNode->prefix_bits = prefix_bits;
    newNode->stem = stem;
    newNode->branch_0 = NULL;
    newNode->branch_1 = NULL;
    newNode->results = NULL;
    return newNode;
}

// Initialises the Patricia tree root node
prefix_node_t* init_ptree(suburb_data *suburb) {
    // Retrieve the key from suburb_data
    char* key = suburb->suburb_name;

    // Initialise the starting node 
    int num_key_bits = (strlen(key) + 1) * BITS_PER_BYTE;
    char* stem = create_stem(key, 0, num_key_bits);
    prefix_node_t* root = create_node(num_key_bits, stem);
    
    // Create a list to hold the suburb data
    root->results = list_create();
    list_append(root->results, suburb);

    return root;
}

// Recursive function which adds a Patricia tree node to an existing tree
void insert_ptree_node(prefix_node_t* node, suburb_data* suburb,
                      int bits_searched) {

    int mismatched_bit = find_mismatch_bit(node->stem, suburb->suburb_name,
                                           node->prefix_bits, bits_searched);
    char* key = suburb->suburb_name;
    int num_key_bits = (strlen(key)+ 1) * BITS_PER_BYTE;

    // Within the length of the stem, no mismatch is found
    if (mismatched_bit == NO_MISMATCH_BIT) {
        // The new node is identical to the stem
        if (node->prefix_bits == num_key_bits) {
            if (node->results == NULL) {
                // Create a results list to hold new suburb_data
                node->results = list_create(); 
            }
            // Add the duplicate to the results llist
            list_append(node->results, suburb);
        } else {
            // The new node is not identical, keep traversing
            if (get_bit(key, (node->prefix_bits + bits_searched)) == 0) {
                if (node->branch_0 == NULL) {
                    // Create new branch 0
                    int new_node_bits = num_key_bits - node->prefix_bits;
                    node->branch_0 = create_node(new_node_bits,
                    create_stem(key, node->prefix_bits, new_node_bits));
                    node->branch_0->results = list_create();
                    list_append(node->branch_0->results, suburb);
                } else {
                    // Traverse existing branch 0
                    bits_searched += node->prefix_bits;
                    insert_ptree_node(node->branch_0, suburb, bits_searched);
                }
            } else {
                if (node->branch_1 == NULL) {
                    // Create new branch 1
                    int new_node_bits = num_key_bits - node->prefix_bits;
                    node->branch_1 = create_node(new_node_bits,
                    create_stem(key, node->prefix_bits, new_node_bits));
                    node->branch_1->results = list_create();
                    list_append(node->branch_1->results, suburb);
                } else {
                    // Traverse existing branch 1
                    bits_searched += node->prefix_bits;
                    insert_ptree_node(node->branch_1, suburb, bits_searched);
                }
            }
        }
    } else {
        // There is a mismatch within the length of the stem

        // First, create a temporary node at the point of mismatch
        // This holds all the bits up until the mismatch
        prefix_node_t* tmp_node = create_node(mismatched_bit,
                                  create_stem(node->stem, 0, mismatched_bit));

        // Second, truncate the original node to the mismatched bit onwards
        char* node_new_stem = create_stem(node->stem, mismatched_bit,
                                          node->prefix_bits - mismatched_bit);
        int node_new_prefix_bits = node->prefix_bits - mismatched_bit;
        prefix_node_t* original_node = create_node(node_new_prefix_bits,
                                                   node_new_stem);
        original_node->branch_0 = node->branch_0;
        original_node->branch_1 = node->branch_1;
        original_node->results = node->results;

        // Last, insert the new key and the original node into the appropriate
        // branches based on the differing bit
        int tmp_node_bits = mismatched_bit + bits_searched;
        if (get_bit(key, tmp_node_bits) == 0) {
            // The key's mismatched bit is 0, so it goes to branch 0
            tmp_node->branch_0 = create_node(num_key_bits - tmp_node_bits,
            create_stem(key, tmp_node_bits, num_key_bits - tmp_node_bits));
            tmp_node->branch_0->results = list_create();
            list_append(tmp_node->branch_0->results, suburb);
            // The old node (root) goes to branch 1
            tmp_node->branch_1 = original_node;
        } else {
            // The key's mismatched bit is 1, so it goes to branch 1
            tmp_node->branch_1 = create_node(num_key_bits - tmp_node_bits,
            create_stem(key, tmp_node_bits, num_key_bits - tmp_node_bits));
            tmp_node->branch_1->results = list_create();
            list_append(tmp_node->branch_1->results, suburb);
            // The old node (root) goes to branch 0
            tmp_node->branch_0 = original_node;
        }

        // Replace the node content with the new created node in place
        free(node->stem);
        *node = *tmp_node;
        free(tmp_node);

    }
}

// Find the first mismatched bit between the current node's stem and the key
// Note that at maximum, this only checks for the length of the stem node
int find_mismatch_bit(char *stem, char *inserted_key, int prefix_bits,
                      int bits_searched) {
    for (int i = 0; i < prefix_bits; i++) {
        if (get_bit(stem, i) != get_bit(inserted_key, (i + bits_searched))) {
            return i;
        }
    }
    return NO_MISMATCH_BIT;
}

// Insert suburb_data into a patricia tree node by first casting void* pointer
void insert_to_ptree(suburb_data* suburb, void** structure) {
    prefix_node_t** root_ptr = (prefix_node_t**)structure;

    // If the root is NULL, initialise the tree
    if (*root_ptr == NULL) {
        *root_ptr = init_ptree(suburb);  // This creates the root node
        return;
    } else {
        // Insert the new node
        insert_ptree_node(*root_ptr, suburb, 0);
    } 
}

// Searching patricia tree >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void search_ptree(prefix_node_t* root, char *search_string, FILE* out_file) {
    fprintf(out_file, "%s -->\n", search_string); 
    int counter = 0;
    int bits = 0;
    int strcmps = 1;
    int nodes_accessed = 0;

    // Return NULL if the tree is empty
    if (root == NULL) {
        stdout_print(counter, search_string, bits, nodes_accessed, strcmps);
        return;
    }

    // Calculate the total number of bits in the search string
    // including the null byte (\0)
    int search_string_bits = (strlen(search_string) + 1) * BITS_PER_BYTE;
    prefix_node_t* currentNode = root;

    // Keeps track of how far we've matched the search string
    int currentBitIndex = 0;  

    // Traverse the tree bit by bit
    while (currentNode != NULL) {
        nodes_accessed++;
        // Compare the current node's stem with the search string
        int mismatchBit = find_mismatch_bit(currentNode->stem, search_string,
                          currentNode->prefix_bits, currentBitIndex);

        // If there is a mismatch within this node, perform a spellcheck
        if (mismatchBit != NO_MISMATCH_BIT) {
            counter++;
            bits += (mismatchBit + 1); // +1 for the mismatched bit
            if (currentNode->results == NULL) {
                // Perform spellcheck
                int *min_dist = (int*)malloc(sizeof(int));
                *min_dist = PLACEHOLDER_MAX;
                prefix_node_t* spellcheck_res = NULL;

                inorder_traversal(currentNode, search_string, min_dist,
                                  &spellcheck_res);
                free(min_dist);

                // Print spellchecked result to stdout & outfile
                stdout_print(counter, search_string, bits, nodes_accessed,
                             strcmps);
                outfile_print(out_file, spellcheck_res->results->head->value);
                return;
            } else {
                // mismatch occurred in a leaf node, return leaf node
                stdout_print(counter, search_string, bits, nodes_accessed,
                             strcmps);
                outfile_print(out_file, currentNode->results->head->value);
                return;
            }
        }

        // Move the current bit index forward by
        // the number of bits in the current node's prefix
        currentBitIndex += currentNode->prefix_bits;
        bits += currentNode->prefix_bits;

        // Check if we are at a leaf node (both branches are NULL)
        if (currentNode->branch_0 == NULL && currentNode->branch_1 == NULL) {
            // Check if the search string fully matches the node
            if (currentBitIndex == search_string_bits) {
                counter++;
                // Exact match found, return the results
                stdout_print(counter, search_string, bits, nodes_accessed,
                             strcmps);
                outfile_print(out_file, currentNode->results->head->value);
                return;
            } else {
                // No match found, search string is longer than the leaf node
                return;
            }
        }

        if (get_bit(search_string, currentBitIndex) == 0) {
            // Move to branch_0 if the current bit is 0
            currentNode = currentNode->branch_0;
        } else {
            // Move to branch_1 if the current bit is 1
            currentNode = currentNode->branch_1;
        }
    }

    return;
}

// Perform an in-order DFS on the nodes past the current one to find node with
// minimum edit distance
void inorder_traversal(prefix_node_t* root, char* search_string, int* min_dist,
                       prefix_node_t** min_node) {
    if (root == NULL) {
        return;
    }

    // Traverse 0 branches
    inorder_traversal(root->branch_0, search_string, min_dist, min_node);

    // Update minimum edit distance found
    if (root->results != NULL) {
        char* key = root->results->head->key;
        int curr_dist = edit_dist(key, search_string, strlen(key),
                                  strlen(search_string));
        if (curr_dist < *min_dist) {
            *min_dist = curr_dist;
            *min_node = root;
        }
    }

    // Traverse 1 branches
    inorder_traversal(root->branch_1, search_string, min_dist, min_node);
}

// Freeing patricia tree >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// Free the patricia tree using postorder traversal
void free_ptree(prefix_node_t* root) {
    if (root == NULL) {
        return;
    }

    // Recursively free the left and right branches (branch_0 and branch_1)
    free_ptree(root->branch_0);
    free_ptree(root->branch_1);

    // Free the stem (bit sequence of the prefix)
    free(root->stem);

    // Free the linked list of results
    if (root->results != NULL) {
        free_llist(root->results);
    }

    // Free the current node itself
    free(root);
}

// Helper Functions taken from spec >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// Allocates new memory to hold the numBits specified and fills the allocated
// memory with the numBits specified starting from the startBit of the oldKey
// array of bytes
char *create_stem(char *oldKey, unsigned int startBit, unsigned int numBits){
    assert(numBits > 0 && startBit >= 0 && oldKey);
    int extraBytes = 0;
    if((numBits % BITS_PER_BYTE) > 0){
        extraBytes = 1;
    }
    int totalBytes = (numBits / BITS_PER_BYTE) + extraBytes;
    char *newStem = malloc(sizeof(char) * totalBytes);
    assert(newStem);
    for(unsigned int i = 0; i < totalBytes; i++){
        newStem[i] = 0;
    }
    for(unsigned int i = 0; i < numBits; i++){
        unsigned int indexFromLeft = i % BITS_PER_BYTE;
        unsigned int offset = (BITS_PER_BYTE - indexFromLeft - 1) % BITS_PER_BYTE;
        unsigned int bitMaskForPosition = 1 << offset;
        unsigned int bitValueAtPosition = get_bit(oldKey, startBit + i);
        unsigned int byteInNewStem = i / BITS_PER_BYTE;
        newStem[byteInNewStem] |= bitMaskForPosition * bitValueAtPosition;
    }
    return newStem;
}

// Helper function. Gets the bit at bitIndex from the string s
int get_bit(char *s, unsigned int bitIndex){
    assert(s && bitIndex >= 0);
    unsigned int byte = bitIndex / BITS_PER_BYTE;
    unsigned int indexFromLeft = bitIndex % BITS_PER_BYTE;
    /* 
        Since we split from the highest order bit first, the bit we are interested
        will be the highest order bit, rather than a bit that occurs at the end of the
        number. 
    */
    unsigned int offset = (BITS_PER_BYTE - (indexFromLeft) - 1) % BITS_PER_BYTE;
    unsigned char byteOfInterest = s[byte];
    unsigned int offsetMask = (1 << offset);
    unsigned int maskedByte = (byteOfInterest & offsetMask);
    /*
        The masked byte will still have the bit in its original position, to return
        either 0 or 1, we need to move the bit to the lowest order bit in the number.
    */
    unsigned int bitOnly = maskedByte >> offset;
    return bitOnly;
}

// Returns min of 3 integers 
// reference: https://www.geeksforgeeks.org/edit-distance-in-c/
int min(int a, int b, int c) {
    if (a < b) {
        if(a < c) {
            return a;
        } else {
            return c;
        }
    } else {
        if(b < c) {
            return b;
        } else {
            return c;
        }
    }
}

// Returns the edit distance of two strings
// reference: https://www.geeksforgeeks.org/edit-distance-in-c/
int edit_dist(char *str1, char *str2, int n, int m) {
    assert(m >= 0 && n >= 0 && (str1 || m == 0) && (str2 || n == 0));
    // Declare a 2D array to store the dynamic programming
    // table
    int dp[n + 1][m + 1];

    // Initialize the dp table
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            // If the first string is empty, the only option
            // is to insert all characters of the second
            // string
            if (i == 0) {
                dp[i][j] = j;
            }
            // If the second string is empty, the only
            // option is to remove all characters of the
            // first string
            else if (j == 0) {
                dp[i][j] = i;
            }
            // If the last characters are the same, no
            // modification is necessary to the string.
            else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = min(1 + dp[i - 1][j], 1 + dp[i][j - 1],
                    dp[i - 1][j - 1]);
            }
            // If the last characters are different,
            // consider all three operations and find the
            // minimum
            else {
                dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1],
                    dp[i - 1][j - 1]);
            }
        }
    }
    // Return the result from the dynamic programming table
    return dp[n][m];
}
