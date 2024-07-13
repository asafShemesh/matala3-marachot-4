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

class DevelopmentCard; // Forward declaration
class Deck;
class CatanGame;

class Player {
public:
    Player(const std::string& name);

    void addResource(const std::string& resource, int amount);
    bool subtractResource(const std::string& resource, int amount);

    void buildCity(int vertex, Board& board);
    bool placeRoad(int start, int end, Board& board, Player &p1, Player &p2, Player &p3); // Change to return bool
    void rollDice(const Board& board, Player &p1, Player &p2, Player &p3); // Update signature
    void placeSettlement(int vertex, Board &board);
    std::vector<int> getVerticesWithDistanceOne(int sourceVertex, const Board &board) const;


    void printPoints() const;
    int getVictoryPoints() const;
    std::string getName() const;
    void buyDevelopmentCard(Deck& deck);
    void useDevelopmentCard(DevCardType cardType, Player& p1, Player& p2, Player& p3, CatanGame catan);

    int getResourceAmount(const std::string& resource) const; // Make public
    bool hasEnoughResources() const; // Make public

private:
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

    bool hasEnoughResourcesForRoad() const; // New method to check road resources
    void deductResources();
    void addDevelopmentCard(const std::string& cardType);

    int getTotalResourceCards() const; // New method to get total resource cards
    void discardHalfResources(); // New method to discard half resources
};
