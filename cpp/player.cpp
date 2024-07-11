#include "player.hpp"
#include "board.hpp"

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

void Player::placeSettelemnt(int plotIndex, Board& board) {
    if (!board.getHouses()[plotIndex]) {
        auto settlement = std::make_unique<House>(HouseType::Settlement, name);
        board.getHouses()[plotIndex] = std::move(settlement);
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
