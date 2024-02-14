CC = gcc
CFLAGS = -g -Wall
ODIR = proj1_out

# List of object files
_OBJ = stack.o queue.o single_linked_node.o double_linked_node.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# Pattern rule to compile object files
$(ODIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

# Main target
main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Additional targets for tests
test1: main.c test1.c
	$(CC) -o $@ $^ $(CFLAGS)

test2: main.c test2.c
	$(CC) -o $@ $^ $(CFLAGS)

test3: main.c test3.c
	$(CC) -o $@ $^ $(CFLAGS)

test4: main.c test4.c
	$(CC) -o $@ $^ $(CFLAGS)

test5: main.c test5.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(ODIR)/*.o main test1 test2 test3 test4 test5

.PHONY: clean
