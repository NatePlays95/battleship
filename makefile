CC=gcc
CFLAGS=-I.
DEPS = grid.h interface.h
OBJ = grid.o interface.o game.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)