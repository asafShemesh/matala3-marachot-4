CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SRC = Main.cpp Resource.cpp Player.cpp catan.cpp Dice.cpp board.cpp Plot.cpp Houses.cpp Road.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = catan

all: $(TARGET)

$(TARGET): $(OBJ)
    $(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
    rm -f $(OBJ) $(TARGET)
