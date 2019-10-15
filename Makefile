CC = g++
CFLAGS = -ggdb3

IDIR = include
ODIR = build
SDIR = src

_INC = Backup.h LinkedList.h Functions.h Scheduler.h
INC = $(patsubst %,$(IDIR)/%,$(_INC))

_OBJ = bsc.o Backup.o LinkedList.o Functions.o Scheduler.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

bsc: $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
