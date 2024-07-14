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

    auto initialPlacements = [&](Player& player, int settlement1, int road1Start, int road1End, int settlement2, int road2Start, int road2End) {
        player.placeSettlement(settlement1, board, catan);
        player.placeRoad(road1Start, road1End, board, p1, p2, p3, catan);
        player.placeSettlement(settlement2, board, catan);
        player.placeRoad(road2Start, road2End, board, p1, p2, p3, catan);
    };

    // Initial placements
    cout << p1.getName() << "'s turn:" << endl;
    initialPlacements(p1, 1, 1, 2, 3, 3, 4);
    catan.nextTurn();
    cout << p2.getName() << "'s turn:" << endl;
    initialPlacements(p2, 5, 5, 6, 7, 7, 8);
    catan.nextTurn();
    cout << p3.getName() << "'s turn:" << endl;
    initialPlacements(p3, 9, 9, 10, 11, 11, 12);
    catan.nextTurn();

    // Player p1's actions
    cout << p1.getName() << "'s turn:" << endl;
    p1.addResource("wood", 1); // Ensure p1 has enough wood
    p1.offerTrade(p2, "wood", 1, "brick", 2, catan);
    catan.nextTurn();

    // Player p2's actions
    cout << p2.getName() << "'s turn:" << endl;
    p2.addResource("brick", 1); // Ensure p2 has enough brick
    p2.offerTrade(p3, "brick", 1, "wheat", 2, catan);
    catan.nextTurn();

    // Player p3's actions
    cout << p3.getName() << "'s turn:" << endl;
    p3.rollDice(board, p1, p2, p3, catan);
    p3.addResource("wheat", 2); // Ensure p3 has enough resources
    p3.addResource("sheep", 1);
    p3.addResource("ore", 1);
    if (p3.hasEnoughResources()) {
        p3.buyDevelopmentCard(deck, catan);
    }
    p3.placeRoad(24, 35, board, p1, p2, p3, catan);
    catan.nextTurn();
    catan.nextTurn();

    // Player p2's additional actions (assuming a turn back to p2)
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
