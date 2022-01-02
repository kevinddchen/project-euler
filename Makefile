CC = g++
CFLAGS = -Wall --std=c++17
SRC = ./src
BIN = ./bin
TARGETS = $(patsubst $(SRC)/%,%,$(wildcard $(SRC)/p*.cxx))
OBJECTS = mathfuncs.o

TAR=$(addprefix $(BIN)/,$(TARGETS))
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
