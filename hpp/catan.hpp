#pragma once
#include "player.hpp"
#include "board.hpp"

class CatanGame {
public:
    CatanGame(Player& p1, Player& p2, Player& p3);

    void nextTurn();
    bool printWinner() const;
    Player& get_turn() const;
    Board& getBoard(); // Updated to return a non-const reference

private:
    Player& player1;
    Player& player2;
    Player& player3;
    Player* currentPlayer;
    int currentPlayerIndex;
    Board board; // Assuming you have a Board class defined
};
