// asaf0604@gmail.com 325362457
#pragma once
#include "board.hpp"

class Player;

class CatanGame
{
public:
    CatanGame(Player &p1, Player &p2, Player &p3);

    void nextTurn();
    bool printWinner() const;
    Player &get_turn() const;
    const Board &getBoardco() const;
    Board &getBoard();

private:
    Player &player1;
    Player &player2;
    Player &player3;
    Player *currentPlayer;
    int currentPlayerIndex;
    Board board;
};
