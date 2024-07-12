# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

# Executable name
EXEC = demo

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj

# Source and object files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

# Include directories
INCLUDES = -I$(INCDIR)

# Default target
all: debug $(EXEC)

# Debug target to print out sources
debug:
	@echo "Source directory: $(SRCDIR)"
	@echo "Sources found: $(wildcard $(SRCDIR)/*.cpp)"
	@echo "SOURCES: $(SOURCES)"
	@echo "OBJECTS: $(OBJECTS)"

# Link object files to create the executable
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

# Clean up build files
clean:
	rm -rf $(OBJDIR) $(EXEC)

# Run the demo
run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run debug
