test_sources := $(wildcard $(SRC)/cpp/tests/*.cpp)
test_apps    := $(subst $(SRC),$(BIN),$(test_sources:.cpp=))
test_objects := $(subst $(SRC),$(OBJ),$(test_sources:.cpp=.o))
test_deps    := $(test_objects:.o=.d)

sources += $(test_sources)
apps    += $(test_apps)
objects += $(test_objects)
deps    += $(test_deps)
