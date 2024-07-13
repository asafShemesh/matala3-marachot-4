# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -fPIC -Ihpp `pkg-config --cflags Qt5Widgets`
LDFLAGS = `pkg-config --libs Qt5Widgets`

# Directories
SRC_DIR = cpp
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = hpp

# Output
MAIN_TARGET = $(BIN_DIR)/Demo

# Source files
MAIN_SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
MAIN_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(MAIN_SRCS))

# Headers
HEADERS = $(wildcard $(INC_DIR)/*.hpp)

# Rules
all: print $(MAIN_TARGET)

# Link the main target
$(MAIN_TARGET): $(MAIN_OBJS)
	@mkdir -p $(BIN_DIR)
	@echo "Linking: $@"
	@echo "Object files: $(MAIN_OBJS)"
	$(CXX) $(CXXFLAGS) -o $@ $(MAIN_OBJS) $(LDFLAGS)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling: $< to $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Print out variables for debugging
print:
	@echo "Source files: $(MAIN_SRCS)"
	@echo "Object files: $(MAIN_OBJS)"
	@echo "Headers: $(HEADERS)"
	@echo "Content of SRC_DIR (cpp):"
	@ls $(SRC_DIR)
	@echo "Content of INC_DIR (hpp):"
	@ls $(INC_DIR)

.PHONY: all clean print
