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
    cout << p1.getName() << "'s turn:" << endl;
    p1.placeSettlement(10, board, catan);
    p1.placeRoad(10, 11, board, p1, p2, p3, catan);
    p1.placeSettlement(12, board, catan);
    p1.placeRoad(12, 11, board, p1, p2, p3, catan);

    // Player p1 offers a trade to Player p2
    p1.addResource("wood", 1); // Ensure p1 has enough wood
    p1.offerTrade(p2, "wood", 1, "brick", 2, catan);

    // Move to the next player
    catan.nextTurn();

    // Player p2's actions
    cout << p2.getName() << "'s turn:" << endl;
    p2.placeSettlement(23, board, catan);
    p2.placeRoad(22, 23, board, p1, p2, p3, catan);
    p2.addResource("brick", 1); // Ensure p2 has enough brick
    p2.offerTrade(p3, "brick", 1, "wheat", 2, catan);

    // Move to the next player
    catan.nextTurn();

    // Player p3's actions
    cout << p3.getName() << "'s turn:" << endl;
    p3.placeSettlement(25, board, catan);
    p3.placeRoad(25, 24, board, p1, p2, p3, catan);
    p3.addResource("wheat", 2); // Ensure p3 has enough resources
    p3.addResource("sheep", 1);
    p3.addResource("ore", 1);
    if (p3.hasEnoughResources()) {
        p3.buyDevelopmentCard(deck, catan);
    }
    p3.placeRoad(24, 35, board, p1, p2, p3, catan);

    // Move to the next player
    catan.nextTurn();

    // Player p2's additional actions (assuming a turn back to p2)
    catan.nextTurn(); // Ensure it's p2's turn again

    cout << p2.getName() << "'s turn:" << endl;
    p2.buildCity(21, board, catan);
    p2.placeRoad(21, 22, board, p1, p2, p3, catan);
    p2.rollDice(board, p1, p2, p3, catan);

    // Print final points
    cout << "Final points:" << endl;
    p1.printPoints();
    p2.printPoints();
    p3.printPoints();

    return 0;
}
