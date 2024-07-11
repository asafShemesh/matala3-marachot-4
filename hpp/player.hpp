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
    
    void buildSettlement(const std::string& location);
    void buildCity(const std::string& location);
    void buildRoad(int start, int end);

    int getVictoryPoints() const;
    std::string getName() const;

private:
    std::vector<std::unique_ptr<DevelopmentCard>> developmentCards;
    std::string name;
    int numSettlements;
    int numCities;
    std::set<std::unique_ptr<House>> mySettlements;
    std::set<std::unique_ptr<House>> myCities;
    std::set<Road> myRoads;

    int wood;   // עץ
    int bricks; // לבנה
    int wheat;  // שיבולת
    int ore;    // ברזל
    int sheep;  // צמר

    int victoryPoints;
};
