#include "Dice.hpp"
#include <cstdlib>
#include <ctime>

Dice::Dice() {
    std::srand(std::time(0));
}

int Dice::roll() {
    // Roll two six-sided dice
    return (std::rand() % 6 + 1) + (std::rand() % 6 + 1);
}
