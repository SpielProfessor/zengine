CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -Isrc -lraylib

SRCDIR = src
BUILDDIR = build
BINDIR = bin
EXAMPLEDIR = examples

LIB = libzEngine.a
EXE = $(BINDIR)/example

# Find all .cpp files under src/
SRC_FILES := $(shell find $(SRCDIR) -name "*.cpp")
OBJ_FILES := $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRC_FILES))

.PHONY: all clean run

all: $(LIB) $(EXE)

# Build static library
$(LIB): $(OBJ_FILES)
	ar rcs $@ $^

# Compile .cpp to .o
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile the example using the static library
$(EXE): $(EXAMPLEDIR)/main.cpp $(LIB)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $< -L. -lzEngine -o $@

# Clean everything
clean:
	rm -rf $(BUILDDIR) $(BINDIR) $(LIB)

# Optional: run the example
run: all
	./$(EXE)

