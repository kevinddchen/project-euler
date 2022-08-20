CC = g++
CFLAGS = -I./include -Wall -std=c++17
SRC = ./src
BIN = ./bin
# automatically recognize binaries corresponding to `.cxx` source files
TARGETS = $(patsubst $(SRC)/%.cxx,$(BIN)/%,$(wildcard $(SRC)/p*.cxx))
TESTS = $(patsubst $(SRC)/tests/%.cxx,$(BIN)/%,$(wildcard $(SRC)/tests/*.cxx))

.PHONY: all test flake clean

all: $(TARGETS) $(TESTS)

$(BIN)/test_mathfuncs: $(SRC)/tests/test_mathfuncs.cxx
	@mkdir -p $(@D)
	$(CC) $< -o $@ $(CFLAGS)

$(BIN)/%: $(SRC)/%.cxx
	@mkdir -p $(@D)
	$(CC) $< -o $@ $(CFLAGS)

test:
	pytest

flake:
	flake8 --config=pyproject.toml

clean:
	rm -rf $(BIN)
