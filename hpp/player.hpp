#pragma once
#include <string>
#include <set>
#include <vector>
#include <memory>
#include "DevelopmentCard.hpp"
#include "Houses.hpp"
#include "Road.hpp"
#include "board.hpp" // Include Board header

class Player {
public:
    Player(const std::string& name);

    void addResource(const std::string& resource, int amount);
    bool subtractResource(const std::string& resource, int amount);

    void placeSettlement(int plotIndex, const Board& board);
    void buildCity(int plotIndex, Board& board);
    void placeRoad(int start, int end);

    void rollDice(); // Added for completeness
    void endTurn(); // Added for completeness
    void trade(Player& other, const std::string& giveResource, const std::string& takeResource, int giveAmount, int takeAmount);
    void buyDevelopmentCard();
    void useDevelopmentCard(DevCardType cardType);

    void printPoints() const;
    int getVictoryPoints() const;
    std::string getName() const;


private:
    std::string name;
    int wood;
    int bricks;
    int wheat;
    int ore;
    int sheep;

    int victoryPoints;
    int numSettlements;
    int numCities;
    int knightCount; // Added for tracking knights

    std::vector<std::unique_ptr<DevCard>> devCards; // Changed to DevCard to match DevelopmentCard.hpp
    std::set<Road> myRoads;
};
