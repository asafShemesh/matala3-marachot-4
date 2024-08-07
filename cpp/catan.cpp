// asaf0604@gmail.com 325362457
#include "catan.hpp"
#include "player.hpp"
#include <iostream>

CatanGame::CatanGame(Player &p1, Player &p2, Player &p3)
    : player1(p1), player2(p2), player3(p3), currentPlayer(&p1), currentPlayerIndex(0) {}

void CatanGame::nextTurn()
{
    currentPlayerIndex = (currentPlayerIndex + 1) % 3;
    if (currentPlayerIndex == 0)
    {
        currentPlayer = &player1;
    }
    else if (currentPlayerIndex == 1)
    {
        currentPlayer = &player2;
    }
    else
    {
        currentPlayer = &player3;
    }
    printWinner();
}

bool CatanGame::printWinner() const
{
    if (player1.getVictoryPoints() >= 10)
    {
        std::cout << player1.getName() << " wins the game!" << std::endl;
        return true;
    }
    else if (player2.getVictoryPoints() >= 10)
    {
        std::cout << player2.getName() << " wins the game!" << std::endl;
        return true;
    }
    else if (player3.getVictoryPoints() >= 10)
    {
        std::cout << player3.getName() << " wins the game!" << std::endl;
        return true;
    }
    return false;
}

Player &CatanGame::get_turn() const
{
    return *currentPlayer;
}

const Board &CatanGame::getBoardco() const
{
    return board;
}

Board &CatanGame::getBoard()
{
    return board;
}
