/*-----------------------------------------------------------------------------
* Project: Assignment 2
* print.c :  
*        = the implementation of the module 'print' of the project
* This module prints results to stdout and the outfile for both stages of the
* project
* Created by Rebecca Chao (rcchao@student.unimelb.edu.au)
* 5/09/2024
-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "print.h"
#include "array.h"
#include "data.h"
#include "linked_list.h"

#define FORMAT_STRING "COMP20003 Code: %d, Official Code Suburb: %d, "\
       "Official Name Suburb: %s, Year: %d, Official Code State: %s, "\
       "Official Name State: %s, Official Code Local Government Area: %s, "\
       "Official Name Local Government Area: %s, Latitude: %.7lf, "\
       "Longitude: %.7lf\n"

// Print suburb to stdout with specified format
void stdout_print(int counter, char* suburb, int bits, int nodes_accessed, int strcmps) {
    if (counter == 0) {
        printf("%s --> NOTFOUND\n", suburb);
    } else {
        printf("%s --> %d records - comparisons: b%d n%d s%d\n", suburb, counter, bits, nodes_accessed, strcmps);
    }
}

// Find and print found suburb to outfile with specified format
void outfile_print(FILE *out_file, suburb_data *value) {
    fprintf(out_file, FORMAT_STRING, value->recordID, value->suburbID,
            value->suburb_name, value->year_recorded, value->state_IDs,
            value->state_names, value->gov_IDs, value->gov_names, 
            value->latitude, value->longitude);
    return;
}

