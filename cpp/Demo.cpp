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
    cout << "Player " << p1.getName() << " is placing initial settlements and roads." << endl;
    p1.placeSettlement(10, board); // Adjust with appropriate vertex
    p1.placeRoad(0, 1, p1, p2, p3);
    p1.placeSettlement(19, board); // Adjust with appropriate vertex
    p1.placeRoad(3, 4, p1, p2, p3);

    // Player p2's actions
    cout << "Player " << p2.getName() << " is placing initial settlements and roads." << endl;
    p2.placeSettlement(20, board); // Adjust with appropriate vertex
    p2.placeRoad(6, 7, p1, p2, p3);
    p2.placeSettlement(21, board); // Adjust with appropriate vertex
    p2.placeRoad(9, 10, p1, p2, p3);

    // Player p3's actions
    cout << "Player " << p3.getName() << " is placing initial settlements and roads." << endl;
    p3.placeSettlement(22, board); // Adjust with appropriate vertex
    p3.placeRoad(12, 13, p1, p2, p3);
    p3.placeSettlement(23, board); // Adjust with appropriate vertex
    p3.placeRoad(15, 16, p1, p2, p3);

    // Simulate turns without loops
    Player& currentPlayer1 = catan.get_turn();
    cout << "It's " << currentPlayer1.getName() << "'s turn." << endl;
    currentPlayer1.rollDice(board, p1, p2, p3);
    catan.nextTurn();

    Player& currentPlayer2 = catan.get_turn();
    cout << "It's " << currentPlayer2.getName() << "'s turn." << endl;
    currentPlayer2.rollDice(board, p1, p2, p3);
    catan.nextTurn();

    Player& currentPlayer3 = catan.get_turn();
    cout << "It's " << currentPlayer3.getName() << "'s turn." << endl;
    currentPlayer3.rollDice(board, p1, p2, p3);
    catan.nextTurn();

    // Print final points and winner
    p1.printPoints();
    p2.printPoints();
    p3.printPoints();
    if (!catan.printWinner()) {
        cout << "No player has reached 10 points yet." << endl;
    }

    return 0;
}
