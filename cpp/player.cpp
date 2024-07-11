#include "player.hpp"
#include "board.hpp"
#include <iostream>

Player::Player(const std::string& name)
    : name(name), wood(0), bricks(0), wheat(0), ore(0), sheep(0), victoryPoints(0), numSettlements(0), numCities(0) {}

void Player::addResource(const std::string& resource, int amount) {
    if (resource == "wood") {
        wood += amount;
    } else if (resource == "bricks") {
        bricks += amount;
    } else if (resource == "wheat") {
        wheat += amount;
    } else if (resource == "ore") {
        ore += amount;
    } else if (resource == "sheep") {
        sheep += amount;
    }
}

bool Player::subtractResource(const std::string& resource, int amount) {
    if (resource == "wood" && wood >= amount) {
        wood -= amount;
        return true;
    } else if (resource == "bricks" && bricks >= amount) {
        bricks -= amount;
        return true;
    } else if (resource == "wheat" && wheat >= amount) {
        wheat -= amount;
        return true;
    } else if (resource == "ore" && ore >= amount) {
        ore -= amount;
        return true;
    } else if (resource == "sheep" && sheep >= amount) {
        sheep -= amount;
        return true;
    }
    return false;
}

void Player::placeSettlement(int plotIndex, const Board& board) {
    if (!board.getHouses()[plotIndex]) { // Ensure getHouses() is a const method
        auto settlement = std::make_unique<House>(HouseType::Settlement, name);
        const_cast<Board&>(board).getHouses()[plotIndex] = std::move(settlement); // Use const_cast to modify
        numSettlements++;
        victoryPoints++;
    }
}


void Player::buildCity(int plotIndex, Board& board) {
    if (board.getHouses()[plotIndex] && board.getHouses()[plotIndex]->getType() == HouseType::Settlement) {
        board.getHouses()[plotIndex]->setType(HouseType::City);
        numCities++;
        numSettlements--; // Assuming a city replaces a settlement
        victoryPoints++; // Increment by 1 for the city, considering the settlement was already counted
    }
}
void Player::printPoints() const {
    std::cout << name << " has " << victoryPoints << " points." << std::endl;
}
void Player::placeRoad(int start, int end) {
    Road road(start, end, name);
    myRoads.insert(road);
}

int Player::getVictoryPoints() const {
    return victoryPoints;
}

std::string Player::getName() const {
    return name;
}

void Player::trade(Player& other, const std::string& giveResource, const std::string& takeResource, int giveAmount, int takeAmount) {
    // Implementation for trading resources
}

void Player::buyDevelopmentCard() {
    // Check if the player has enough resources (1 ore, 1 wool, 1 wheat)
    // If yes, deduct resources and randomly assign a development card

    int randomCard = rand() % 5;
    switch (randomCard) {
        case 0:
            devCards.push_back(std::make_unique<MonopolyCard>());
            break;
        case 1:
            devCards.push_back(std::make_unique<RoadBuildingCard>());
            break;
        case 2:
            devCards.push_back(std::make_unique<YearOfPlentyCard>());
            break;
        case 3:
            devCards.push_back(std::make_unique<KnightCard>());
            break;
        case 4:
            devCards.push_back(std::make_unique<VictoryPointCard>());
            victoryPoints++;
            break;
    }
}

void Player::useDevelopmentCard(DevCardType cardType) {
    for (auto it = devCards.begin(); it != devCards.end(); ++it) {
        if ((*it)->getType() == cardType) {
            switch (cardType) {
                case DevCardType::Monopoly:
                    // Implementation for Monopoly
                    break;
                case DevCardType::RoadBuilding:
                    // Implementation for Road Building
                    break;
                case DevCardType::YearOfPlenty:
                    // Implementation for Year of Plenty
                    break;
                case DevCardType::Knight:
                    knightCount++;
                    if (knightCount == 3) {
                        // Award Largest Army card
                        victoryPoints += 2;
                    }
                    break;
                case DevCardType::VictoryPoint:
                    // Victory points are already awarded when the card is drawn
                    break;
            }
            devCards.erase(it);
            break;
        }
    }
}

