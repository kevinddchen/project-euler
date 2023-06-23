CC = g++
CFLAGS = -I./src/cpp/include -Wall -std=c++17 -O2
SRC = ./src/solutions
BIN = ./bin
TESTS = ./tests
# automatically recognize binaries corresponding to `.cxx` source files
TARGETS = $(patsubst $(SRC)/%.cxx,$(BIN)/%,$(wildcard $(SRC)/p*.cxx))
TEST_TARGETS = $(patsubst $(TESTS)/%.cxx,$(BIN)/%,$(wildcard $(TESTS)/*.cxx))

.PHONY: all clean

all: $(TARGETS) $(TESTS_TARGETS)

$(BIN)/test_mathfuncs: $(TESTS)/test_mathfuncs.cxx
	@mkdir -p $(@D)
	$(CC) $< -o $@ $(CFLAGS)

$(BIN)/%: $(SRC)/%.cxx
	@mkdir -p $(@D)
	$(CC) $< -o $@ $(CFLAGS)

clean:
	rm -rf $(BIN)
