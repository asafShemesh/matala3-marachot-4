#include "deck.hpp"
#include <algorithm>
#include <random>

Deck::Deck() {
    initializeDeck();
}

void Deck::initializeDeck() {
    cards = {
        "Monopoly",
        "Road Building",
        "Year of Plenty",
        "Knight", "Knight", "Knight",
        "Victory Point", "Victory Point", "Victory Point", "Victory Point"
    };
    // Shuffle the deck
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

std::string Deck::drawCard() {
    if (cards.empty()) {
        return "No cards left";
    }
    std::string card = cards.back();
    cards.pop_back();
    return card;
}
