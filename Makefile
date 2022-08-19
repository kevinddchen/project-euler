CC = g++
CFLAGS = -I./include -Wall -std=c++17
SRC = ./src
BIN = ./bin
# automatically recognize binaries corresponding to `.cxx` source files
TARGETS = $(patsubst $(SRC)/%.cxx,$(BIN)/%,$(wildcard $(SRC)/p*.cxx))
TESTS = $(patsubst $(SRC)/tests/%.cxx,$(BIN)/%,$(wildcard $(SRC)/tests/*.cxx))

.PHONY: all prepare clean

all: $(TARGETS) $(TESTS)

prepare:
	mkdir -p $(BIN)

$(BIN)/test_mathfuncs: $(SRC)/tests/test_mathfuncs.cxx prepare
	$(CC) $< -o $@ $(CFLAGS)

$(BIN)/%: $(SRC)/%.cxx prepare
	$(CC) $< -o $@ $(CFLAGS)

clean:
	rm -rf $(BIN)
