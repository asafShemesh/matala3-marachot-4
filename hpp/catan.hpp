#pragma once
#include "board.hpp"
#include "player.hpp"
#include <memory>

class CatanGame {
public:
    Board board;
    CatanGame(Player& player1, Player& player2, Player& player3);
    void startGame();
    void playTurn();
    bool isGameOver() const;
    Player get_turn() const;
    const Board& getBoard() const; // Ensure this returns a const reference

private:
    Player& player1;
    Player& player2;
    Player& player3;
    Player* currentPlayer;
    int currentPlayerIndex;

    void nextTurn();
};
