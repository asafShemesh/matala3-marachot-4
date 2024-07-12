#include <iostream>
#include <stdexcept>
#include <vector>
#include "catan.hpp"
#include "player.hpp"
#include "board.hpp"
#include "deck.hpp"

using namespace std;
using namespace ariel;

int main() {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Deck deck; // Assuming Deck is properly defined and used in the game
    CatanGame catan(p1, p2, p3);

    // Starting of the game. Every player places two settlements and two roads.
    Board& board = catan.getBoard(); // get the board of the game as a non-const reference

    // The following functions depend on implementations not provided in the first 20 lines:
    // Assuming placeSettlement, placeRoad, rollDice, endTurn, trade, buyDevelopmentCard,
    // printPoints, printWinner exist and are implemented correctly

    // Player p1's actions
    p1.placeSettlement(5, 6, 7, board);
    p1.placeRoad(5, 6, p1, p2, p3);
    p1.placeSettlement(3, 4, 5, board);
    p1.placeRoad(3, 4, p1, p2, p3);

    // Player p2's actions
    p2.placeSettlement(8, 9, 10, board);
    p2.placeRoad(8, 9, p1, p2, p3);

    try {
        p3.placeSettlement(8, 9, 10, board); // p3 tries to place a settlement in the same location as p2.
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    p2.placeSettlement(11, 12, 13, board);
    p2.placeRoad(11, 12, p1, p2, p3);

    // Player p3's actions
    p3.placeSettlement(14, 15, 16, board);
    p3.placeRoad(14, 15, p1, p2, p3);

    // Turn sequence
    p1.rollDice(board, deck, p1, p2, p3); // Adjusted to pass all players and the deck
    p1.placeRoad(5, 6, p1, p2, p3); // p1 continues to build a road.
    catan.nextTurn();

    p2.rollDice(board, deck, p1, p2, p3); // Adjusted to pass all players and the deck
    catan.nextTurn();

    p3.rollDice(board, deck, p1, p2, p3); // Adjusted to pass all players and the deck
    catan.nextTurn();

    try {
        p2.rollDice(board, deck, p1, p2, p3); // p2 tries to roll the dice again, but it's not his turn.
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    p1.rollDice(board, deck, p1, p2, p3); // Adjusted to pass all players and the deck
    p1.trade(p2, "wood", "bricks", 1, 1); // p1 trades 1 wood for 1 brick with p2.
    catan.nextTurn();

    p2.rollDice(board, deck, p1, p2, p3); // Adjusted to pass all players and the deck
    p2.buyDevelopmentCard(deck); // p2 buys a development card. Let's say it is a bonus points card.
    catan.nextTurn();

    p1.printPoints(); // p1 has 2 points because it has two settlements.
    p2.printPoints(); // p2 has 3 points because it has two settlements and a bonus points card.
    p3.printPoints(); // p3 has 2 points because it has two settlements.

    if (!catan.printWinner()) {
        cout << "No player has reached 10 points yet." << endl;
    }
}
