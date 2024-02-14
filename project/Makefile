CC = gcc # Flag for implicit rules
CFLAGS = -g -Wall # Flag for implicit rules. Turn on debug info
#from https://makefiletutorial.com/
ODIR=proj1_out
LDIR =../lib

_OBJ = stack.o queue.o single_linked_node.o double_linked_node.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.c
	$(CC) $(CFLAGS) main.c 
test1: %.c
	$(CC) $(CFLAGS) -c main.c -o main.o 1 test1.c # from https://www.gnu.org/software/make/manual/make.html
test2: %.c 
	$(CC) $(CFLAGS) -c main.c -o main.o 1 test2.c # from https://www.gnu.org/software/make/manual/make.html
test2: %.c 
	$(CC) $(CFLAGS) -c main.c -o main.o 1 test3.c # from https://www.gnu.org/software/make/manual/make.html
test4: %.c 
	$(CC) $(CFLAGS) -c main.c -o main.o 1 test4.c # from https://www.gnu.org/software/make/manual/make.html
test5: %.c 
	$(CC) $(CFLAGS) -c main.c -o main.o 1 test5.c # from https://www.gnu.org/software/make/manual/make.html

clean:
	rm -f *.o compile
.PHONY: build clean
