/*-----------------------------------------------------------------------------
* Project: Assignment 1
* process.h :  
*        = the interface of the module 'process' of the project
* Created by Amy Sun (axsun@student.unimelb.edu.au)
* and Rebecca Chao (rcchao@student.unimelb.edu.au)
* 15/08/2024
-----------------------------------------------------------------------------*/
#ifndef _PROCESS_H_
#define _PROCESS_H_

// type definitions >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef struct {
	int recordID; 
	int suburbID;
	char* suburb_name; 
	int year_recorded;
	char* state_IDs;
	char* state_names;
	char* gov_IDs;
	char* gov_names;
	double latitude;
	double longitude;
} suburb_data;

typedef struct node node_t;

struct node { 
	char* key;          // suburb name
	suburb_data* value; // suburb data
	node_t *next;       // pointer to the next node
};

typedef struct list {
	node_t *head;  // points to the first node of the list
	node_t *tail;  // points to the last node of the list 
} list_t;


// processing functions >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Processes the input dataset into a list_t
list_t* process_file_content(FILE *file);

// Parses one line of input data and stores it
void parse_line(char* line, ssize_t line_len, list_t*);

// Store one field into suburb_data
void process_field(suburb_data *suburb, int field, const char *tmp);

// Reads in user input for one suburb string, stores it dynamically 
// and returns the pointer
char* get_string();

// Put together and returns s 2d array that has the user input suburbs
char** all_suburbs();

// linked-list functions >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Creates & returns an empty linked list
// based on listCreate function from COMP20003 Workshop 3.4
list_t *list_create();

// Inserts a new node with value "value" to the end of "list" 
void list_append(list_t *list, suburb_data *value);

#endif
