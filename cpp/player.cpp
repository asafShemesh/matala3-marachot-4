#include "Player.hpp"

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

void Player::buildSettlement(const std::string& location) {
    auto settlement = std::make_unique<House>(HouseType::Settlement, name);
    mySettlements.insert(std::move(settlement));
    numSettlements++;
    victoryPoints++;
}

void Player::buildCity(const std::string& location) {
    for (auto it = mySettlements.begin(); it != mySettlements.end(); ++it) {
        if ((*it)->getOwner() == name && (*it)->getType() == HouseType::Settlement) {
            (*it)->setType(HouseType::City);
            auto city = std::move(*it);
            mySettlements.erase(it);
            myCities.insert(std::move(city));
            numCities++;
            numSettlements--; // Assuming a city replaces a settlement
            victoryPoints++; // Increment by 1 for the city, considering the settlement was already counted
            break;
        }
    }
}

void Player::buildRoad(int start, int end) {
    Road road(start, end, name);
    myRoads.insert(road);
}

int Player::getVictoryPoints() const {
    return victoryPoints;
}

std::string Player::getName() const {
    return name;
}
