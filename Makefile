CC = g++
CFLAGS = -I./src/cpp/include -I./src/cpp/thirdparty/eigen -Wall -std=c++20 -O2
SRC = ./src/solutions
BIN = ./bin
TESTS = ./src/cpp/tests

# automatically recognize targets corresponding to `.cxx` source files
TARGETS = $(patsubst $(SRC)/%.cxx,$(BIN)/%,$(wildcard $(SRC)/p*.cxx))
TEST_TARGETS = $(patsubst $(TESTS)/%.cxx,$(BIN)/%,$(wildcard $(TESTS)/test_*.cxx))

.PHONY: all tests clean

all: $(TARGETS)

tests: $(TEST_TARGETS)

$(BIN)/%: $(TESTS)/%.cxx
	@mkdir -p $(@D)
	$(CC) -o $@ $(CFLAGS) $^

$(BIN)/%: $(SRC)/%.cxx
	@mkdir -p $(@D)
	$(CC) -o $@ $(CFLAGS) $^

clean:
	rm -rf $(BIN)
