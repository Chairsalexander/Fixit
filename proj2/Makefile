CC = gcc
CFLAGS = -g -Wall
ODIR = proj1_out
LDIR = ../lib
_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.c
	$(CC) $(CFLAGS) -o $@ $^

compile: main.c
	$(CC) $(CFLAGS) -o main main.c

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o main