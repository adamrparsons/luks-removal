CC = gcc
CFLAGS = -ansi -Wall -pedantic -g
OBJ = luks-removal.o
EXEC = luks-removal

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

luks-removal.o : luks-removal.c luks-removal.h
	$(CC) $(CFLAGS) -c luks-removal.c

clean :
	rm -rf $(OBJ) $(EXEC)