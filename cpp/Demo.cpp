#include <iostream>
#include <stdexcept>
#include <vector>
#include "catan.hpp"
#include "player.hpp"
#include "board.hpp"

using namespace std;
using namespace ariel;

int main() {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    CatanGame catan(p1, p2, p3);

    // Starting of the game. Every player places two settlements and two roads.
    const Board& board = catan.getBoard(); // get the board of the game.

    // The following functions depend on implementations not provided in the first 20 lines:
    // Assuming placeSettlement, placeRoad, rollDice, endTurn, trade, buyDevelopmentCard,
    // printPoints, printWinner exist and are implemented correctly

    // Player p1's actions
    p1.placeSettlement(5, board);
    p1.placeSettlement(6, board);
    p1.placeRoad(5, 6);
    p1.placeSettlement(3, board);
    p1.placeSettlement(4, board);
    p1.placeRoad(3, 4);

    // Player p2's actions
    p2.placeSettlement(4, board);
    p2.placeSettlement(9, board);
    p2.placeRoad(4, 9);
    try {
        p3.placeSettlement(4, board); // p3 tries to place a settlement in the same location as p2.
        p3.placeSettlement(9, board); // p3 tries to place a settlement in the same location as p2.
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }
    p2.placeSettlement(9, board);   
    p2.placeSettlement(5, board);
    p2.placeRoad(5, 9);

    // Player p3's actions
    p3.placeSettlement(3, board);
    p3.placeSettlement(8, board);
    p3.placeRoad(3, 8);
    p3.placeSettlement(9, board);
    p3.placeSettlement(3, board);
    p3.placeRoad(3, 9);

    // Turn sequence
    p1.rollDice();                                    // Let's say it prints 4. Then, p2 gets ore from the mountains.
    p1.placeRoad(5, 6); // p1 continues to build a road.
    p1.endTurn();                                     // p1 ends his turn.

    p2.rollDice(); // Let's say it prints 9. Then, p3 gets wool from the Pasture Land, p2 gets wool from the Pasture Land.
    p2.endTurn();  // p2 ends his turn.

    p3.rollDice(); // Let's say it prints 3. Then, p3 gets wheat from the Agricultural Land and Ore from the Mountains, p1 gets wheat from the Agricultural Land.
    p3.endTurn();  // p3 ends his turn.

    try {
        p2.rollDice(); // p2 tries to roll the dice again, but it's not his turn.
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    p1.rollDice();                       // Let's say it prints 6. Then, p1 gets bricks from the hills.
    p1.trade(p2, "wood", "brick", 1, 1); // p1 trades 1 wood for 1 brick with p2.
    p1.endTurn();                        // p1 ends his turn.

    p2.rollDice();           // Let's say it prints 9. Then, p3 gets wool from the Pasture Land, p2 gets wool from the Pasture Land.
    p2.buyDevelopmentCard(); // p2 buys a development card. Let's say it is a bonus points card.
    p2.endTurn();            // p2 ends his turn.

    p1.printPoints(); // p1 has 2 points because it has two settlements.
    p2.printPoints(); // p2 has 3 points because it has two settlements and a bonus points card.
    p3.printPoints(); // p3 has 2 points because it has two settlements.

    catan.printWinner(); // Should print None because no player reached 10 points.
}
