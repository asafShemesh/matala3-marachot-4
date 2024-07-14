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

    void buildCity(int vertex, Board& board, CatanGame &catan); // Update signature
    bool placeRoad(int start, int end, Board& board, Player &p1, Player &p2, Player &p3, CatanGame &catan); // Update signature
    void rollDice(const Board& board, Player &p1, Player &p2, Player &p3, CatanGame &catan); // Update signature
    void placeSettlement(int vertex, Board &board, CatanGame &catan); // Update signature
    std::vector<int> getVerticesWithDistanceOne(int sourceVertex, const Board &board) const;

    void printPoints() const;
    int getVictoryPoints() const;
    std::string getName() const;
    void buyDevelopmentCard(Deck& deck, CatanGame &catan); // Update signature
    void useDevelopmentCard(DevCardType cardType, Player& p1, Player& p2, Player& p3, CatanGame &catan); // Update signature
    bool offerTrade(Player& otherPlayer, const std::string& giveResource, int giveAmount, const std::string& receiveResource, int receiveAmount, CatanGame &catan); // New method

    int getResourceAmount(const std::string& resource) const; // Make public
    bool hasEnoughResources() const; // Make public
    int getKnightCount() const; 

private:
    bool isPlayerTurn(const CatanGame &catan) const; // New helper method
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
