#include "player.hpp"
#include "board.hpp"
#include "DevelopmentCard.hpp"
#include "deck.hpp"
#include "catan.hpp"
#include <iostream>

Player::Player(const std::string &name)
    : name(name), wood(0), bricks(0), wheat(0), ore(0), sheep(0), victoryPoints(0), numSettlements(0), numCities(0) {}

int Player::roll()
{
    return (std::rand() % 6 + 1) + (std::rand() % 6 + 1);
}
void Player::rollDice(const Board &board, Player &p1, Player &p2, Player &p3)
{
    std::vector<Player *> players = {&p1, &p2, &p3};
    int diceValue = roll();

    std::cout << getName() << " rolled a " << diceValue << "." << std::endl;

    // If the roll is 7, handle resource discarding
    if (diceValue == 7)
    {
        std::cout << "A 7 was rolled. Players must discard half of their resources if they have more than 7." << std::endl;
        for (Player *player : players)
        {
            if (player->getTotalResourceCards() > 7)
            {
                player->discardHalfResources();
            }
        }
        return; // No resource collection happens on a roll of 7
    }

    // Each player collects resources based on the dice roll
    std::unordered_set<std::shared_ptr<Plot>> collectedPlots;
    for (Player *player : players)
    {
        const auto &houses = board.getHouses(); // Access const houses
        for (const auto &house : houses)
        {
            if (house && house->getOwner() == player->getName())
            {
                for (const auto &plot : house->getAdjacentPlots())
                {
                    if (plot->getNumber() == diceValue && collectedPlots.find(plot) == collectedPlots.end())
                    {
                        int amount = (house->getType() == HouseType::Settlement) ? 1 : 2;
                        player->addResource(plot->getType(), amount);
                        collectedPlots.insert(plot); // Mark the plot as collected
                    }
                }
            }
        }
    }
}

void Player::addResource(const std::string &resource, int amount)
{
    if (resource == "Wood")
    {
        wood += amount;
        std::cout << this->getName() << " collects " << amount << " wood." << std::endl;
    }
    else if (resource == "Brick")
    {
        bricks += amount;
        std::cout << this->getName() << " collects " << amount << " bricks." << std::endl;
    }
    else if (resource == "Wheat")
    {
        wheat += amount;
        std::cout << this->getName() << " collects " << amount << " wheat." << std::endl;
    }
    else if (resource == "Ore")
    {
        ore += amount;
        std::cout << this->getName() << " collects " << amount << " ore." << std::endl;
    }
    else if (resource == "Sheep")
    {
        sheep += amount;
        std::cout << this->getName() << " collects " << amount << " sheep." << std::endl;
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

int Player::getTotalResourceCards() const
{
    return wood + bricks + wheat + ore + sheep;
}

void Player::discardHalfResources()
{
    int totalResources = getTotalResourceCards();
    int cardsToDiscard = totalResources / 2;

    // Discard resources in a balanced way
    while (cardsToDiscard > 0)
    {
        if (wood > 0 && cardsToDiscard > 0)
        {
            subtractResource("wood", 1);
            cardsToDiscard--;
        }
        if (bricks > 0 && cardsToDiscard > 0)
        {
            subtractResource("bricks", 1);
            cardsToDiscard--;
        }
        if (wheat > 0 && cardsToDiscard > 0)
        {
            subtractResource("wheat", 1);
            cardsToDiscard--;
        }
        if (ore > 0 && cardsToDiscard > 0)
        {
            subtractResource("ore", 1);
            cardsToDiscard--;
        }
        if (sheep > 0 && cardsToDiscard > 0)
        {
            subtractResource("sheep", 1);
            cardsToDiscard--;
        }
    }
}

void Player::printPoints() const
{
    std::cout << name << " has " << victoryPoints << " points." << std::endl;
}

int Player::getVictoryPoints() const
{
    return victoryPoints;
}

std::string Player::getName() const
{
    return name;
}
void Player::placeSettlement(int vertex, Board &board)
{
    auto &houses = board.getMutableHouses(); // Use a non-const version to modify the houses
    auto &plots = board.getMutablePlots();

        // Check if the vertex already has a settlement
        for (const auto &house : houses)
        {
            if (house && house->getVertex() == vertex)
            {
                std::cout << "Cannot place a settlement on vertex " << vertex << " because it already has a house owned by " << house->getOwner() << "." << std::endl;
                return; // Cannot place a settlement if the vertex already has a house
            }
        }

        // Check for adjacent vertices connected by a valid road
        std::unordered_set<int> validVertices;
        for (const auto &plot : plots)
        {
            for (const auto &v : plot->getVertices())
            {
                if (validRoad(vertex, v, board))
                {
                    validVertices.insert(v);
                }
            }
        }

        // Ensure no vertex from those valid vertices has a house
        for (const auto &v : validVertices)
        {
            for (const auto &house : houses)
            {
                if (house && house->getVertex() == v)
                {
                    std::cout << "Cannot place a settlement adjacent to another settlement on vertex " << v << "." << std::endl;
                    return;
                }
            }
        }

    // Check if the player needs to pay resources
    if (numCities + numSettlements >= 2)
    {
        if (!(wood >= 1 && sheep >= 1 && bricks >= 1 && wheat >= 1))
        {
            std::cout << "Not enough resources to place a settlement." << std::endl;
            return; // Not enough resources to place a settlement
        }
        subtractResource("bricks", 1);
        subtractResource("sheep", 1);
        subtractResource("wood", 1);
        subtractResource("wheat", 1);
    }

    // Find the plots adjacent to the vertex
    std::vector<std::shared_ptr<Plot>> adjacentPlots;
    for (auto &plot : plots)
    {
        if (plot->getVertices().count(vertex) > 0)
        {
            adjacentPlots.push_back(plot);
        }
    }

    // Place the settlement
    auto settlement = std::make_unique<House>(HouseType::Settlement, name, vertex, adjacentPlots);
    House *settlementPtr = settlement.get(); // Get raw pointer before moving

    // Assign raw pointers to the house array
    houses[vertex] = settlementPtr;

    // Move the unique pointer to the Board's unique pointer array to maintain ownership
    board.addHouse(std::move(settlement));

    numSettlements++;
    victoryPoints++;
    std::cout << name << " placed a settlement on vertex " << vertex << "." << std::endl;

    // Give resources from adjacent plots for the first two settlements
    if (numCities + numSettlements <= 2)
    {
        for (const auto &plot : settlementPtr->getAdjacentPlots())
        {
            addResource(plot->getType(), 1);
        }
    }
}


bool Player::validRoad(int vertex1, int vertex2, const Board &board) const
{
    const auto &plots = board.getPlots(); // Get the plots from the board

    // Iterate through each plot to check if the vertices are on the same plot edge
    for (const auto &plot : plots)
    {
        const auto &vertices = plot->getVertices();
        
        // Check if both vertices are in the plot's vertex set
        if (vertices.count(vertex1) > 0 && vertices.count(vertex2) > 0)
        {
            // Check if vertex1 and vertex2 are adjacent in the plot
            auto it1 = vertices.find(vertex1);
            auto it2 = vertices.find(vertex2);

            // Ensure the vertices are adjacent (check the order in the set)
            if (it1 != vertices.end() && it2 != vertices.end())
            {
                // Assuming the vertices are stored in a circular manner
                auto next = std::next(it1);
                if (next == vertices.end())
                    next = vertices.begin();
                
                auto prev = (it1 == vertices.begin()) ? std::prev(vertices.end()) : std::prev(it1);

                if (*next == vertex2 || *prev == vertex2)
                {
                    return true; // The vertices are adjacent
                }
            }
        }
    }

    return false; // The vertices are not adjacent
}






bool Player::placeRoad(int startVertex, int endVertex, Player &p1, Player &p2, Player &p3)
{
    // If the player has fewer than 2 roads, they can place the road for free
    if (myRoads.size() >= 2)
    {
        if (!hasEnoughResourcesForRoad())
        {
            std::cout << "Not enough resources to place a road." << std::endl;
            return false;
        }

        subtractResource("wood", 1);
        subtractResource("bricks", 1);
    }

    Road road(startVertex, endVertex, name);
    std::vector<Player *> players = {&p1, &p2, &p3};

    // Check if the road already exists for any player
    for (const auto &player : players)
    {
        if (player->myRoads.find(road) != player->myRoads.end())
        {
            std::cout << "Road already exists between these points." << std::endl;
            return false;
        }
    }

    myRoads.insert(road);
    return true;
}

// void Player::trade(Player &other, const std::string &giveResource, const std::string &takeResource, int giveAmount, int takeAmount)
// {
//     // Implementation for trading resources
// }

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
                placeRoad(start1, end1, p1, p2, p3);
                std::cout << "Enter the start and end points for the second road: ";
                std::cin >> start2 >> end2;
                placeRoad(start2, end2, p1, p2, p3);
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
