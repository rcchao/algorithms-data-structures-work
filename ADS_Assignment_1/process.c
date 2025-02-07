/*-----------------------------------------------------------------------------
* Project: Assignment 1
* process.c :  
*        = the implementation of the module 'process' of the project
* Created by Amy Sun (axsun@student.unimelb.edu.au)
* and Rebecca Chao (rcchao@student.unimelb.edu.au)
* 15/08/2024
-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "process.h"

#define MAX_FIELD_LEN 128
#define DBL_QUOTES '\"'
#define COMMA ','
#define DYNAMIC 2

// Processing functions >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// Processes the input dataset into a list_t
list_t* process_file_content(FILE *file) {
    char *line = NULL;
    size_t len = 0;
    ssize_t line_len;
    ssize_t read;
    list_t *dict = list_create();

    // Read header 
    getline(&line, &len, file);
    // Read each line, find its length and parse it
    while ((read = getline(&line, &len, file)) != -1) {
        line_len = read;
        parse_line(line, line_len, dict);
    }

    // Free the allocated buffer
    free(line);

    return dict;
}

// Parses one line of input data and stores it
void parse_line(char* line, ssize_t line_len, list_t* dict){
    char tmp[MAX_FIELD_LEN]; 
    int in_quote = 0;
    
    int field = 0;
    suburb_data *suburb = malloc(sizeof(suburb_data));
    assert(suburb);

    char ch;
    int j = 0, i = 0;

    while ((ch = line[i])) {
        if (ch == DBL_QUOTES) {
            // End of quote
            if (in_quote) {
                in_quote = 0;
            // Beginning of quote
            } else {
                in_quote = 1;
            }
        }

        // End of field has been reached
        if(((ch == COMMA) && !in_quote) || i == (line_len - 1)){
            tmp[j] = '\0';
            // Pass field into suburb_data
            process_field(suburb, field, tmp);
            // Reset array that temporarily holds the field
            for (int k = 0; k < MAX_FIELD_LEN; k++) {
                tmp[k] = '\0';
            }
            j = 0;
            field++;
        // Still within field, add character to field
        } else if (ch != DBL_QUOTES) {
            tmp[j++] = ch; 
        }
        i++;
        }
    // Finally, append the data to the dict
    list_append(dict, suburb);
    return;
}

// Store one field into suburb_data
void process_field(suburb_data *suburb, int field, const char *tmp) {
    switch (field) { 
        case 0:
            suburb->recordID = atoi(tmp); 
            break;
        case 1:
            suburb->suburbID = atoi(tmp); 
            break;
        case 2:
            suburb->suburb_name = strdup(tmp); 
            break;
        case 3:
            suburb->year_recorded = atoi(tmp); 
            break;
        case 4:
            suburb->state_IDs = strdup(tmp); 
            break;
        case 5:
            suburb->state_names = strdup(tmp); 
            break;
        case 6:
            suburb->gov_IDs = strdup(tmp); 
            break;
        case 7:
            suburb->gov_names = strdup(tmp);
            break;
        case 8:
            suburb->latitude = strtod(tmp, NULL); 
            break;
        case 9:
            suburb->longitude = strtod(tmp, NULL); 
            break;
        default:
            break;
    }
}

// Reads in user input for one suburb string, stores it dynamically 
// and returns the pointer
char* get_string() {
    char c;
    size_t len = 0, current_size = DYNAMIC;
    char *suburb = (char*) calloc(current_size, sizeof(char));
    assert(suburb);

    while ((c = getchar()) != EOF && c != '\n') {
        suburb[len++] = c;
        if (len == current_size) {
            size_t old_size = current_size;
            current_size *= DYNAMIC;
            suburb = realloc(suburb, current_size * sizeof(char));
            assert(suburb);
            // Recalloc
            int size_diff = (current_size - old_size) * sizeof(char);
            memset(suburb + old_size, 0, size_diff);
        }
    }
    return suburb;
}

// Put together and returns s 2d array that has the user input suburbs
char** all_suburbs() {
    size_t max_size = DYNAMIC;
    size_t num_strings = 0;
    char **suburbs = (char**) calloc(max_size, sizeof(char*));
    assert(suburbs);

    while (1) {
        char *word = get_string();
        // End of input when an empty string is returned
        if (strlen(word) == 0) { 
            free(word);
            break;
        }
        suburbs[num_strings++] = word;
        if (num_strings == max_size) {
            max_size *= DYNAMIC;
            suburbs = realloc(suburbs, max_size * sizeof(char*));
            assert(suburbs);
        }
    }
    memset(suburbs + num_strings, 0, (max_size - num_strings) * sizeof(char*));
    assert(suburbs);
    return suburbs;
}

// linked-list functions >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Creates & returns an empty linked list
// based on listCreate function from COMP20003 Workshop 3.4
list_t *list_create() {
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



