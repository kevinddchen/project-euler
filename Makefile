CC = g++
CFLAGS = -I./include -Wall -std=c++17 -O2
SRC = ./src
BIN = ./bin
TST = ./tests
# automatically recognize binaries corresponding to `.cxx` source files
TARGETS = $(patsubst $(SRC)/%.cxx,$(BIN)/%,$(wildcard $(SRC)/p*.cxx))
TESTS = $(patsubst $(TST)/%.cxx,$(BIN)/%,$(wildcard $(TST)/*.cxx))

.PHONY: all clean

all: $(TARGETS) $(TESTS)

$(BIN)/test_mathfuncs: $(TST)/test_mathfuncs.cxx
	@mkdir -p $(@D)
	$(CC) $< -o $@ $(CFLAGS)

$(BIN)/%: $(SRC)/%.cxx
	@mkdir -p $(@D)
	$(CC) $< -o $@ $(CFLAGS)

clean:
	rm -rf $(BIN)
