CC = gcc
CFLAGS = -g -Wall
ODIR = proj3_out
LDIR = ../lib
_OBJ = sched_sim.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

sched_sim: sched_sim.c
	$(CC) $(CFLAGS) -o $@ $^



.PHONY: clean

clean:
	rm -f $(ODIR)/*.o sched_sim
