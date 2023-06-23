CC = g++
CFLAGS = -I$(LIB) -Wall -std=c++17 -O2

LIB = ./src/cpp/include
BIN = ./bin
SOLS = ./src/solutions
TESTS = ./tests

# automatically recognize binaries corresponding to `.cxx` source files
TARGETS = $(patsubst $(SOLS)/%.cxx,$(BIN)/%,$(wildcard $(SOLS)/p*.cxx))
TEST_TARGETS = $(patsubst $(TESTS)/%.cxx,$(BIN)/%,$(wildcard $(TESTS)/*.cxx))

.PHONY: all clean

all: $(TARGETS) $(TESTS_TARGETS)

$(BIN)/test_mathfuncs: $(TESTS)/test_mathfuncs.cxx
	@mkdir -p $(@D)
	$(CC) $< -o $@ $(CFLAGS)

$(BIN)/%: $(SOLS)/%.cxx
	@mkdir -p $(@D)
	$(CC) $< -o $@ $(CFLAGS)

clean:
	rm -rf $(BIN)
