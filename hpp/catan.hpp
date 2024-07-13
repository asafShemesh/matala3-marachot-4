#pragma once
#include "board.hpp"

class Player; // Forward declaration

class CatanGame {
public:
    CatanGame(Player& p1, Player& p2, Player& p3);

    void nextTurn();
    bool printWinner() const;
    Player& get_turn() const;
    const Board& getBoardco() const; // Const version
    Board& getBoard(); // Non-const version

private:
    Player& player1;
    Player& player2;
    Player& player3;
    Player* currentPlayer;
    int currentPlayerIndex;
    Board board;
};
