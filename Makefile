## Project file structure ##
IDIR = include
SRCDIR = src
ODIR = obj

## CC compiler options ##
CC = gcc
CFLAGS = -Wall -I$(IDIR)
LIBS = -lm

_DEPS = performance-metrics.h files.h
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ = performance-metrics.o files.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

## Compilation ##
$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

obtain-performance-metrics: $(OBJ)
	$(CC) -o $@ main.c $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~