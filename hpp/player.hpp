#pragma once
#include <string>
#include <set>
#include <vector>
#include <memory>
#include "DevelopmentCard.hpp"
#include "Houses.hpp"
#include "Road.hpp"
#include "catan.hpp"
#include "board.hpp"

class DevelopmentCard; // Forward declaration
class Deck;

class Player {
public:
    Player(const std::string& name);

    void addResource(const std::string& resource, int amount);
    bool subtractResource(const std::string& resource, int amount);

    void placeSettlement(int plot1Index, int plot2Index, int plot3Index, Board& board);
    void buildCity(int plot1Index, int plot2Index, int plot3Index, Board& board);
    bool placeRoad(int start, int end, Player &p1, Player &p2, Player &p3); // Change to return bool

    void rollDice(const Board& board, Deck &deck, Player &p1, Player &p2, Player &p3); // Update signature

    void printPoints() const;
    int getVictoryPoints() const;
    std::string getName() const;
    void trade(Player& other, const std::string& giveResource, const std::string& takeResource, int giveAmount, int takeAmount);
    void buyDevelopmentCard(Deck& deck);
    void useDevelopmentCard(DevCardType cardType, Player& p1, Player& p2, Player& p3, CatanGame catan);

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

    bool hasEnoughResources() const;
    bool hasEnoughResourcesForRoad() const; // New method to check road resources
    void deductResources();
    void addDevelopmentCard(const std::string& cardType);
    int getResourceAmount(const std::string& resource) const;

    int getTotalResourceCards() const; // New method to get total resource cards
    void discardHalfResources(Deck &deck); // New method to discard half resources
};
