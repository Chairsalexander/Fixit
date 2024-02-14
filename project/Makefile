CC = gcc
CFLAGS = -g -Wall
ODIR = proj1_out
LDIR =../lib

_OBJ = stack.o queue.o single_linked_node.o double_linked_node.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.c
	$(CC) -o $@ $^ $(CFLAGS)

test1: main.c test1.c
	$(CC) $(CFLAGS) -o test1 main.c test1.c

test2: main.c test2.c
	$(CC) $(CFLAGS) -o test2 main.c test2.c

test3: main.c test3.c
	$(CC) $(CFLAGS) -o test3 main.c test3.c

test4: main.c test4.c
	$(CC) $(CFLAGS) -o test4 main.c test4.c

test5: main.c test5.c
	$(CC) $(CFLAGS) -o test5 main.c test5.c

clean:
	rm -f $(ODIR)/*.o main test1 test2 test3 test4 test5
.PHONY: clean
