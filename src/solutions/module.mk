solution_sources := $(wildcard $(SRC)/solutions/*.cpp)
solution_apps    := $(subst $(SRC),$(BIN),$(solution_sources:.cpp=))
solution_objects := $(subst $(SRC),$(OBJ),$(solution_sources:.cpp=.o))
solution_deps    := $(solution_objects:.o=.d)

apps    += $(solution_apps)
sources += $(solution_sources)
objects += $(solution_objects)
deps    += $(solution_deps)
