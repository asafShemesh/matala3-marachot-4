# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -fPIC -Ihpp `pkg-config --cflags Qt5Widgets`
LDFLAGS = `pkg-config --libs Qt5Widgets`

# Directories
SRC_DIR = cpp
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = hpp
TEST_DIR = tests

# Output
MAIN_TARGET = $(BIN_DIR)/Demo
TEST_TARGET = $(BIN_DIR)/test_catan

# Source files
MAIN_SRCS = $(filter-out $(TEST_DIR)/test_catan.cpp, $(wildcard $(SRC_DIR)/*.cpp))
TEST_SRCS = $(TEST_DIR)/test_catan.cpp

# Object files
MAIN_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(MAIN_SRCS))
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TEST_SRCS))

# Headers
HEADERS = $(wildcard $(INC_DIR)/*.hpp)

# Rules
all: print $(MAIN_TARGET) $(TEST_TARGET)

# Link the main target
$(MAIN_TARGET): $(MAIN_OBJS)
	@mkdir -p $(BIN_DIR)
	@echo "Linking: $@"
	@echo "Object files: $(MAIN_OBJS)"
	$(CXX) $(CXXFLAGS) -o $@ $(MAIN_OBJS) $(LDFLAGS)

# Link the test target
$(TEST_TARGET): $(TEST_OBJS) $(filter-out $(OBJ_DIR)/Demo.o, $(MAIN_OBJS))
	@mkdir -p $(BIN_DIR)
	@echo "Linking: $@"
	@echo "Object files: $(TEST_OBJS) $(filter-out $(OBJ_DIR)/Demo.o, $(MAIN_OBJS))"
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling: $< to $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling: $< to $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the executable
catan: $(MAIN_TARGET)
	@echo "Running: $(MAIN_TARGET)"
	./$(MAIN_TARGET)

# Run the tests
test: $(TEST_TARGET)
	@echo "Running tests: $(TEST_TARGET)"
	./$(TEST_TARGET)

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Print out variables for debugging
print:
	@echo "Source files: $(MAIN_SRCS)"
	@echo "Test files: $(TEST_SRCS)"
	@echo "Object files: $(MAIN_OBJS) $(TEST_OBJS)"
	@echo "Headers: $(HEADERS)"
	@echo "Content of SRC_DIR (cpp):"
	@ls $(SRC_DIR)
	@echo "Content of INC_DIR (hpp):"
	@ls $(INC_DIR)
	@echo "Content of TEST_DIR (tests):"
	@ls $(TEST_DIR)

.PHONY: all clean print catan test
