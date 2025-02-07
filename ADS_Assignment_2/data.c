/*-----------------------------------------------------------------------------
* Project: Assignment 2
* data.c :
*        = the implementation of the module 'data' of the project
* This data agnostic module processes a CSV of known format into the input
* structure (linked list or a patricia tree)
* Created by Rebecca Chao (rcchao@student.unimelb.edu.au)
* 5/09/2024
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "data.h"

#define MAX_FIELD_LEN 128
#define DBL_QUOTES '\"'
#define COMMA ','
#define DYNAMIC 2

// Processes the input dataset into the input structure
void* process_file_content(FILE *file, 
                           void (*insert_func)(suburb_data*, void**), 
                           void** structure) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // Read header 
    getline(&line, &len, file);

    // Read each line and parse it
    while ((read = getline(&line, &len, file)) != -1) {
        parse_line(line, read, insert_func, structure);
    }

    free(line);
    return *structure;
}

// Parses one line of input data and stores it in the input structure
void parse_line(char* line, ssize_t line_len,
                            void (*insert_func)(suburb_data*, void**),
                            void** structure) {
    char tmp[MAX_FIELD_LEN]; 
    int in_quote = 0;
    int field = 0;
    suburb_data *suburb = malloc(sizeof(suburb_data));
    assert(suburb);

    char ch;
    int j = 0, i = 0;

    while ((ch = line[i])) {
        if (ch == DBL_QUOTES) {
            // Toggle in_quote
            in_quote = !in_quote;  
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

    // Call the passed function to insert suburb_data into the chosen structure
    insert_func(suburb, structure);
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

// Freeing suburb_data struct >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void suburb_free(suburb_data *value) {
	free(value->suburb_name);
	value->suburb_name = NULL;
	free(value->state_IDs);
	value->state_IDs = NULL;
	free(value->state_names);
	value->state_names = NULL;
	free(value->gov_IDs);
	value->gov_IDs = NULL;
	free(value->gov_names);
	value->gov_names = NULL;
	free(value);
	value = NULL;
};
