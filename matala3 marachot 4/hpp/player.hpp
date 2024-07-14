// asaf0604@gmail.com 325362457
#pragma once
#include <string>
#include <set>
#include <vector>
#include <unordered_set>
#include <memory>
#include "DevelopmentCard.hpp"
#include "Houses.hpp"
#include "Road.hpp"
#include "catan.hpp"
#include "board.hpp"

class DevelopmentCard;
class Deck;
class CatanGame;

class Player
{
public:
    Player(const std::string &name);

    void addResource(const std::string &resource, int amount);
    bool subtractResource(const std::string &resource, int amount);

    void buildCity(int vertex, Board &board, CatanGame &catan);
    bool placeRoad(int start, int end, Board &board, Player &p1, Player &p2, Player &p3, CatanGame &catan);
    void rollDice(const Board &board, Player &p1, Player &p2, Player &p3, CatanGame &catan);
    void placeSettlement(int vertex, Board &board, CatanGame &catan);
    std::vector<int> getVerticesWithDistanceOne(int sourceVertex, const Board &board) const;

    void printPoints() const;
    int getVictoryPoints() const;
    std::string getName() const;
    void buyDevelopmentCard(Deck &deck, CatanGame &catan);
    void useDevelopmentCard(DevCardType cardType, Player &p1, Player &p2, Player &p3, CatanGame &catan);
    bool offerTrade(Player &otherPlayer, const std::string &giveResource, int giveAmount, const std::string &receiveResource, int receiveAmount, CatanGame &catan);

    int getResourceAmount(const std::string &resource) const;
    bool hasEnoughResources() const;
    int getKnightCount() const;

private:
    bool isPlayerTurn(const CatanGame &catan) const;
    int roll();
    std::string name;
    int wood;
    int bricks;
    int wheat;
    int ore;
    int sheep;

    int victoryPoints;
    int numSettlements;
    int numCities;
    int knightCount;

    std::set<Road> myRoads;
    std::vector<std::unique_ptr<DevelopmentCard>> devCards;

    bool hasEnoughResourcesForRoad() const;
    void deductResources();
    void addDevelopmentCard(const std::string &cardType);

    int getTotalResourceCards() const;
    void discardHalfResources();
};
