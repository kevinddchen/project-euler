test_sources := $(wildcard $(SRC)/cpp/tests/*.cxx)
test_apps    := $(subst $(SRC),$(BIN),$(test_sources:.cxx=))
test_objects := $(subst $(SRC),$(OBJ),$(test_sources:.cxx=.o))
test_deps    := $(test_objects:.o=.d)

sources += $(test_sources)
apps    += $(test_apps)
objects += $(test_objects)
deps    += $(test_deps)
