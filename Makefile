## Project file structure ##
IDIR = include
SRCDIR = src
ODIR = obj

## CC compiler options ##
CC = gcc
CFLAGS = -g -Wall -I$(IDIR) -O2 -fopenmp
LIBS = -lm

_DEPS = metrics.h ds.h
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ = metrics.o ds.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

## Compilation ##
$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

obtain-performance-metrics: $(OBJ)
	$(CC) -o $@ main.c $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~