CC = gcc
CFLAGS = -g -Wall
ODIR = proj1_out
LDIR =../lib

_OBJ = stack.o queue.o single_linked_node.o double_linked_node.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

all: main test1 test2 test3 test4 test5

main: main.c
	$(CC) -o $@ $^ $(CFLAGS)

test1: test1.c
	$(CC) $(CFLAGS) -o test1 test1.c

test2: test2.c
	$(CC) $(CFLAGS) -o test2 test2.c

test3: test3.c
	$(CC) $(CFLAGS) -o test3 test3.c

test4: test4.c
	$(CC) $(CFLAGS) -o test4 test4.c

test5: test5.c
	$(CC) $(CFLAGS) -o test5 test5.c

clean:
	rm -f $(ODIR)/*.o main test1 test2 test3 test4 test5
.PHONY: clean
