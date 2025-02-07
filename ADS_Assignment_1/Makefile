# Define C compiler & flags
CC = gcc
CFLAGS = -Wall -g
# Define libraries to be linked (for example -lm)
LDLIBS = 

# Define set of implementation source files and object files
SRC = driver.c process.c search.c delete.c free.c
# OBJ is the same as SRC, just replace .c with .o
OBJ = $(SRC:.c=.o)
 
# Define the executable name(s)
EXE = dict1 dict2

# the first target:
dict1: $(OBJ)  
	$(CC) $(CFLAGS) -o dict1 $(OBJ) $(LDLIBS)

dict2: $(OBJ)  
	$(CC) $(CFLAGS) -o dict2 $(OBJ) $(LDLIBS)

# Other targets specify what .o files rely on
driver.o: driver.c 
process.o: process.c process.h 
search.o: search.c search.h
free.o: free.c free.h
delete.o: delete.c delete.h

clean:
	rm -f $(OBJ) $(OBJ2) $(EXE)
