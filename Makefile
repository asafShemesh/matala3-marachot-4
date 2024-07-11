CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SRC = Main.cpp Resource.cpp Player.cpp CatanGame.cpp Dice.cpp Board.cpp Plot.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = catan

all: $(TARGET)

$(TARGET): $(OBJ)
    $(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
    rm -f $(OBJ) $(TARGET)
