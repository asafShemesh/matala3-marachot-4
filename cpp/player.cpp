#include "player.hpp"
#include "board.hpp"
#include "DevelopmentCard.hpp"
#include "deck.hpp"
#include "catan.hpp"
#include <iostream>

Player::Player(const std::string &name)
    : name(name), wood(0), bricks(0), wheat(0), ore(0), sheep(0), victoryPoints(0), numSettlements(0), numCities(0) {}

void Player::addResource(const std::string &resource, int amount)
{
    if (resource == "wood")
    {
        wood += amount;
    }
    else if (resource == "bricks")
    {
        bricks += amount;
    }
    else if (resource == "wheat")
    {
        wheat += amount;
    }
    else if (resource == "ore")
    {
        ore += amount;
    }
    else if (resource == "sheep")
    {
        sheep += amount;
    }
}

int Player::roll()
{
    return (std::rand() % 6 + 1) + (std::rand() % 6 + 1);
}

void Player::rollDice(const Board &board)
{
    int diceValue = roll();
    const auto &houses = board.getHouses(); // Access const houses
    for (auto &house : houses)
    {
        if (house)
        {
            for (const auto &plot : house->getAdjacentPlots())
            {
                if (plot->getNumber() == diceValue)
                {
                    int amount = (house->getType() == HouseType::Settlement) ? 1 : 2;
                    addResource(plot->getType(), amount);
                }
            }
        }
    }
}

bool Player::subtractResource(const std::string &resource, int amount)
{
    if (resource == "wood" && wood >= amount)
    {
        wood -= amount;
        return true;
    }
    else if (resource == "bricks" && bricks >= amount)
    {
        bricks -= amount;
        return true;
    }
    else if (resource == "wheat" && wheat >= amount)
    {
        wheat -= amount;
        return true;
    }
    else if (resource == "ore" && ore >= amount)
    {
        ore -= amount;
        return true;
    }
    else if (resource == "sheep" && sheep >= amount)
    {
        sheep -= amount;
        return true;
    }
    return false;
}

void Player::placeSettlement(int plot1Index, int plot2Index, int plot3Index, Board &board)
{
    auto &houses = board.getMutableHouses(); // Use a non-const version to modify the houses
    auto &plots = board.getPlots();

    // Check if any of the plots already have a settlement at the intersection
    for (int i : {plot1Index, plot2Index, plot3Index})
    {
        if (houses[i])
        {
            return; // Cannot place a settlement if any of the plots already has a house
        }
    }

    // Place the settlement
    auto settlement = std::make_unique<House>(HouseType::Settlement, name, std::array<std::shared_ptr<Plot>, 3>{plots[plot1Index], plots[plot2Index], plots[plot3Index]});
    House *settlementPtr = settlement.get(); // Get raw pointer before moving

    // Assign raw pointers to the house array
    houses[plot1Index] = settlementPtr;
    houses[plot2Index] = settlementPtr;
    houses[plot3Index] = settlementPtr;

    // Move the unique pointer to the Board's unique pointer array to maintain ownership
    board.addHouse(std::move(settlement));

    numSettlements++;
    victoryPoints++;

    // Give resources from adjacent plots
    for (const auto &plot : settlementPtr->getAdjacentPlots())
    {
        addResource(plot->getType(), 1);
    }
}

void Player::buildCity(int plot1Index, int plot2Index, int plot3Index, Board &board)
{
    auto &houses = board.getHouses();
    std::array<int, 3> plots = {plot1Index, plot2Index, plot3Index};

    bool canBuild = true;
    for (int i : plots)
    {
        if (!houses[i] || houses[i]->getType() != HouseType::Settlement)
        {
            canBuild = false;
            break;
        }
    }

    if (canBuild)
    {
        for (int i : plots)
        {
            houses[i]->setType(HouseType::City);
        }
        numCities++;
        numSettlements--;
        victoryPoints++;
    }
}

void Player::printPoints() const
{
    std::cout << name << " has " << victoryPoints << " points." << std::endl;
}
bool Player::placeRoad(int start, int end,  Player &p1, Player &p2, Player &p3) {
    if (!hasEnoughResourcesForRoad()) {
        std::cout << "Not enough resources to place a road." << std::endl;
        return false;
    }

    Road road(start, end, name);
    std::vector<Player *> players = {&p1, &p2, &p3};
    // Check if the road already exists for any player
    for (const auto& player : players) {
        if (player.myRoads.find(road) != player.myRoads.end()) {
            std::cout << "Road already exists between these points." << std::endl;
            return false;
        }
    }

    myRoads.insert(road);
    subtractResource("wood", 1);
    subtractResource("bricks", 1);
    return true;
}


int Player::getVictoryPoints() const
{
    return victoryPoints;
}

std::string Player::getName() const
{
    return name;
}

void Player::trade(Player &other, const std::string &giveResource, const std::string &takeResource, int giveAmount, int takeAmount)
{
    // Implementation for trading resources
}

void Player::buyDevelopmentCard(Deck &deck)
{
    if (!hasEnoughResources())
    {
        throw std::runtime_error("Not enough resources to buy a development card");
    }

    deductResources();
    std::string cardType = deck.drawCard();
    addDevelopmentCard(cardType);
}

bool Player::hasEnoughResources() const
{
    return ore >= 1 && sheep >= 1 && wheat >= 1;
}

void Player::deductResources()
{
    ore -= 1;
    sheep -= 1;
    wheat -= 1;
}

void Player::addDevelopmentCard(const std::string &cardType)
{
    if (cardType == "Monopoly")
    {
        devCards.push_back(std::make_unique<MonopolyCard>());
    }
    else if (cardType == "Road Building")
    {
        devCards.push_back(std::make_unique<RoadBuildingCard>());
    }
    else if (cardType == "Year of Plenty")
    {
        devCards.push_back(std::make_unique<YearOfPlentyCard>());
    }
    else if (cardType == "Knight")
    {
        devCards.push_back(std::make_unique<KnightCard>());
    }
    else if (cardType == "Victory Point")
    {
        devCards.push_back(std::make_unique<VictoryPointCard>());
        victoryPoints++;
    }
}

void Player::useDevelopmentCard(DevCardType cardType, Player &p1, Player &p2, Player &p3, CatanGame catan)
{
    for (auto it = devCards.begin(); it != devCards.end(); ++it)
    {
        if ((*it)->getType() == cardType)
        {
            switch (cardType)
            {
            case DevCardType::Monopoly:
            {
                std::string chosenResource;
                std::cout << "Choose a resource: wood, bricks, wheat, ore, sheep: ";
                std::cin >> chosenResource;
                std::vector<Player *> players = {&p1, &p2, &p3};
                for (Player *player : players)
                {
                    if (player != this)
                    {
                        int amount = player->getResourceAmount(chosenResource);
                        player->subtractResource(chosenResource, amount);
                        addResource(chosenResource, amount);
                    }
                }
                catan.nextTurn();
                break;
            }
            case DevCardType::RoadBuilding:
            {
                int start1, end1, start2, end2;
                std::cout << "Enter the start and end points for the first road: ";
                std::cin >> start1 >> end1;
                placeRoad(start1, end1,p1,p2,p3);
                std::cout << "Enter the start and end points for the second road: ";
                std::cin >> start2 >> end2;
                placeRoad(start2, end2, p1,p2,p3);
                catan.nextTurn();
                break;
            }
            case DevCardType::YearOfPlenty:
            {
                std::string resource1, resource2;
                std::cout << "Choose first resource: wood, bricks, wheat, ore, sheep: ";
                std::cin >> resource1;
                std::cout << "Choose second resource: wood, bricks, wheat, ore, sheep: ";
                std::cin >> resource2;
                addResource(resource1, 1);
                addResource(resource2, 1);
                break;
            }
            case DevCardType::Knight:
                knightCount++;
                if (knightCount == 3)
                {
                    victoryPoints += 2;
                }
                catan.nextTurn();
                break;
            case DevCardType::VictoryPoint:
                victoryPoints += 1;
                catan.nextTurn();
                break;
            }
            devCards.erase(it);
            break;
        }
    }
}

bool Player::hasEnoughResourcesForRoad() const
{
    return wood >= 1 && bricks >= 1;
}

int Player::getResourceAmount(const std::string &resource) const
{
    if (resource == "wood")
    {
        return wood;
    }
    else if (resource == "bricks")
    {
        return bricks;
    }
    else if (resource == "wheat")
    {
        return wheat;
    }
    else if (resource == "ore")
    {
        return ore;
    }
    else if (resource == "sheep")
    {
        return sheep;
    }
    return 0;
}
