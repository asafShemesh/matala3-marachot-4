#pragma once
#include "board.hpp"
#include "player.hpp"
#include <memory>

class CatanGame {
public:
    Board board;
    CatanGame(Player& player1, Player& player2, Player& player3);
    bool printWinner() const;
    Player get_turn() const;
    const Board& getBoard() const; // Ensure this returns a const reference
    void nextTurn();

private:
    Player& player1;
    Player& player2;
    Player& player3;
    Player* currentPlayer;
    int currentPlayerIndex;

};
