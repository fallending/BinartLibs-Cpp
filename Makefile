# CC := g++ -std=c++14
# CFLAGS := -Wall -I.

# SRCDIR = src
# BUILDDIR = build
# TESTDIR = test

# SOURCES := $(wildcard $(SRCDIR)/*.cpp)
# SRC_OBJS := $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)
# TESTS   := $(wildcard $(TESTDIR)/*.cpp)
# TEST_OBJS := $(TESTS:$(TESTDIR)/%.cpp=$(BUILDDIR)/%.o)

build:
	mkdir build && cd build && cmake .. && cmake --build .

test:
	cd build && ctest && ./bin/unit_tests

clean:
	rm -rf build

reset:
	git clean -d -f -x
