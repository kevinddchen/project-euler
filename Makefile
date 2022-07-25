CC = g++
CFLAGS = -Wall --std=c++17
SRC = ./src
BIN = ./bin
OBJECTS = mathfuncs.o

# automatically recognize binaries corresponding to `.cxx` source files
TAR=$(patsubst $(SRC)/%.cxx,$(BIN)/%,$(wildcard $(SRC)/p*.cxx))
OBJ=$(addprefix $(BIN)/,$(OBJECTS))

all : $(TAR)

$(BIN)/mathfuncs.o : $(SRC)/mathfuncs.cxx $(SRC)/mathfuncs.h
	mkdir -p $(BIN)
	$(CC) $< -o $@ -c $(CFLAGS)

$(BIN)/% : $(SRC)/%.cxx $(OBJ)
	$(CC) $< $(OBJ) -o $@ $(CFLAGS)

.PHONY : all clean

clean :
	rm -f $(OBJ) $(TAR)
