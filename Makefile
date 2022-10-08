CC = g++
CFLAGS = -I./include -Wall -std=c++17 -O2
SRC = ./src
BIN = ./bin
# automatically recognize binaries corresponding to `.cxx` source files
TARGETS = $(patsubst $(SRC)/%.cxx,$(BIN)/%,$(wildcard $(SRC)/p*.cxx))
TESTS = $(patsubst $(SRC)/tests/%.cxx,$(BIN)/%,$(wildcard $(SRC)/tests/*.cxx))

.PHONY: all tests flake clean

all: $(TARGETS) $(TESTS)

$(BIN)/test_mathfuncs: $(SRC)/tests/test_mathfuncs.cxx
	@mkdir -p $(@D)
	$(CC) $< -o $@ $(CFLAGS)

$(BIN)/%: $(SRC)/%.cxx
	@mkdir -p $(@D)
	$(CC) $< -o $@ $(CFLAGS)

tests:
	pytest

flake:
	flake8

clean:
	rm -rf $(BIN)
