#pragma once
#include <vector>
#include <string>

class Deck {
public:
    Deck();
    std::string drawCard();

private:
    std::vector<std::string> cards;
    void initializeDeck();
};
