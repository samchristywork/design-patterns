CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra

SRCS := $(shell find creational structural behavioral -name '*.cpp' | sort)
BINS := $(patsubst %.cpp, build/%, $(SRCS))

.PHONY: all run clean $(addprefix run-, $(BINS))

all: $(BINS)

build/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/%: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@

run: all
	@for bin in $(BINS); do \
		echo ""; \
		echo "=== $$bin ==="; \
		./$$bin; \
	done
