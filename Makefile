# https://stackoverflow.com/a/25966957

BIN := bin
SRC := src
OBJ := objects

# These will be added to as we include the modules
sources := $(wildcard $(SRC)/solutions/p*.cpp)
apps    := $(subst $(SRC),$(BIN),$(sources:.cpp=))
objects := $(subst $(SRC),$(OBJ),$(sources:.cpp=.o))
deps    := $(objects:.o=.d)

include $(SRC)/cpp/tests/module.mk

-include $(deps)

CXX      := g++
CPPFLAGS := -I./src/cpp -I./src/cpp/thirdparty/eigen -MMD -MP
CXXFLAGS := -std=c++20 -O3 -Wall -Wextra -pedantic-errors
LDFLAGS  :=
LDLIBS   :=

# Link apps
$(BIN)/%: $(OBJ)/%.o
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

# Compile objects
$(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: all
all: $(apps) $(objects)

.PHONY: clean
clean:
	$(RM) -r $(BIN)/* $(OBJ)/*

.PHONY: tests
tests: $(test_apps)
