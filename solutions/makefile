CC = g++
CFLAGS = -O
TARGETS = p357
OBJECTS = cmathfuncs.o

all: $(TARGETS)

cmathfuncs.o: cmathfuncs.cxx
	$(CC) -o $@ cmathfuncs.cxx -c $(CFLAGS)

p357: p357.cxx $(OBJECTS)
	$(CC) -o $@ p357.cxx $(OBJECTS) $(CFLAGS)

clean: 
	rm -f *.o $(TARGETS)
