mf_sources := $(wildcard $(SRC)/cpp/mf/*.cpp)
mf_objects := $(subst $(SRC),$(OBJ),$(mf_sources:.cpp=.o))
mf_deps    := $(mf_objects:.o=.d)

sources += $(mf_sources)
objects += $(mf_objects)
deps    += $(mf_deps)
