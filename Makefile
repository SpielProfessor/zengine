CXX = g++
CXXFLAGS = -std=gnu++20 -Wall -Wextra -Iinclude -Isrc -lraylib -O0 -g
CXXFLAGS_RELEASE = -std=gnu++20 -Wall -Wextra -Iinclude -Isrc -lraylib -O3

SRCDIR = src
BUILDDIR = build
BINDIR = bin
EXAMPLEDIR = examples

LIB = libzEngine.a
EXE = $(BINDIR)/example $(BINDIR)/exampleTilemap $(BINDIR)/exampleTilemapLayer $(BINDIR)/exampleAnimatedSprite

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
$(BINDIR)/%: $(EXAMPLEDIR)/%.cpp $(LIB)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $< -L. -lzEngine -o $@

# Clean everything
clean:
	rm -rf $(BUILDDIR) $(BINDIR) $(LIB)

# Optional: run the example
run: all
	./$(EXE)

