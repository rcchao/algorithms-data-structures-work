# algorithms-data-structures-work
ADS work in C

Both projects 1 and 2 were created with the intention of efficiently storing, querying and managing a dataset of Australian suburbs. Project 1 was implemented using a linked list while Project 2 was implemented using a Radix tree. As part of project 2 I also made a report to compare the two data structures analysing and comparing their time and memory complexity.
- 100% for proj 1, done in collaboration with Amy Sun
- 93.3% for proj 2, done individually

Project 1: Designing and implementing a linked-list based dictionary from scratch in C 
Features:
- Search tool which searches for a key in the list and outputs any records which match the key
- Removal tool which removes all records associated with a set of specified keys and outputs all remaining records at the end to a new CSV file
Technical learnings:
- Involved creating and using a Makefile
- Modularised the code across files appropriately
- Utilised low-level memory management and pointer manipulation to create a robust and efficient linked list structure

Project 2: Implementing a radix-tree based dictionary from scratch in C
Features:
- Enhanced search functionality which handles three cases:
- Exact matches – output all records which match the query key
- Similar matches – if no exact match is found, the closest key (measured by bit) is output with its associated records
- No matches – handle cases in which no matches are found
Technical learnings:
- Involved building a data agnostic nodule which required using function pointers
- Involved using low level manipulations (bitwise operations) on binary data
  
