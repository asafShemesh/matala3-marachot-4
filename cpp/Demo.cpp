#include <iostream>
#include <stdexcept>
#include <vector>
#include "catan.hpp"
#include "player.hpp"
#include "board.hpp"
#include "deck.hpp"

using namespace std;

int main() {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Deck deck; // Assuming Deck is properly defined and used in the game
    CatanGame catan(p1, p2, p3);
    vector<Player *> players = {&p1, &p2, &p3};

    // Starting the game. Every player places two settlements and two roads.
    Board& board = catan.getBoard(); // Use the non-const version to get the board

    // Player p1's actions
    p1.placeSettlement(10, board);
    p1.placeRoad(10, 11,board, p1, p2, p3);
    p1.placeSettlement(19, board);
    p1.placeRoad(11, 19,board, p1, p2, p3);

    // Player p2's actions
    p2.placeSettlement(21, board);
    p2.placeRoad(21, 22,board,  p1, p2, p3);
    p2.placeSettlement(12, board);
    p2.placeRoad(12, 13,board,  p1, p2, p3);

    // Player p3's actions
    p3.placeSettlement(23, board);
    p3.placeRoad(23, 24,board,  p1, p2, p3);
    p3.placeSettlement(15, board);
    p3.placeRoad(15, 16,board,  p1, p2, p3);

    // Print final points
    p1.printPoints();
    p2.printPoints();
    p3.printPoints();

    return 0;
}
