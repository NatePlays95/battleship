CC=gcc
CFLAGS=-I.
DEPS = grid.h
OBJ = grid.o game.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)