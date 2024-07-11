#pragma once
#include <string>
#include <set>
#include <vector>
#include <memory>
#include "DevelopmentCard.hpp"
#include "Houses.hpp"
#include "Road.hpp"

class Player {
public:
    Player(const std::string& name);
    
    void addResource(const std::string& resource, int amount);
    bool subtractResource(const std::string& resource, int amount);
    
    void placeSettelemnt(int plotIndex, Board& board);
    void buildCity(int plotIndex, Board& board);
    void buildRoad(int start, int end);

    int getVictoryPoints() const;
    std::string getName() const;

private:
    std::vector<std::unique_ptr<DevelopmentCard>> developmentCards;
    std::string name;
    int numSettlements;
    int numCities;
    std::set<Road> myRoads;

    int wood;  
    int bricks;
    int wheat; 
    int ore;  
    int sheep; 

    int victoryPoints;
};
