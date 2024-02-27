CC = g++ # Flag for implicit rules
CFLAGS = -g -Wall # Flag for implicit rules. Turn on debug info
#from https://makefiletutorial.com/
ODIR=proj1_out
LDIR =../lib

_OBJ = 1
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

proj2: main.cpp
	$(CC) $(CFLAGS) main.cpp #from Computing II lecture notes
compile: main.cpp
	$(CC) $(CFLAGS) -o main main.cpp
	./main
clean:
	rm -f *.o compile
.PHONY: build clean
