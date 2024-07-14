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

bool Player::isPlayerTurn(const CatanGame &catan) const {
    return &catan.get_turn() == this;
}

void Player::rollDice(const Board &board, Player &p1, Player &p2, Player &p3, CatanGame &catan)
{
    if (!isPlayerTurn(catan)) {
        std::cerr << "It's not " << getName() << "'s turn." << std::endl;
        return;
    }

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
    if (resource == "wood")
    {
        wood += amount;
        std::cout << this->getName() << " collects " << amount << " wood." << std::endl;
    }
    else if (resource == "bricks")
    {
        bricks += amount;
        std::cout << this->getName() << " collects " << amount << " bricks." << std::endl;
    }
    else if (resource == "wheat")
    {
        wheat += amount;
        std::cout << this->getName() << " collects " << amount << " wheat." << std::endl;
    }
    else if (resource == "ore")
    {
        ore += amount;
        std::cout << this->getName() << " collects " << amount << " ore." << std::endl;
    }
    else if (resource == "sheep")
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

void Player::placeSettlement(int vertex, Board &board, CatanGame &catan) {
    if (!isPlayerTurn(catan)) {
        std::cerr << "It's not " << getName() << "'s turn." << std::endl;
        return;
    }

    auto &houses = board.getMutableHouses();
    auto &plots = board.getMutablePlots();

    // Validate the vertex index
    if (vertex < 0 || vertex >= static_cast<int>(houses.size())) {
        std::cerr << "Error: Vertex index " << vertex << " is out of bounds for houses array." << std::endl;
        return;
    }

    // Check if the vertex already has a settlement
    if (houses[vertex]) {
        std::cerr << "Cannot place a settlement on vertex " << vertex << " because it already has a house." << std::endl;
        return;
    }

    std::vector<int> adjacentVertices = getVerticesWithDistanceOne(vertex, board);
    for (const auto &v : adjacentVertices) {
        if (houses[v]) {
            std::cerr << "Cannot place a settlement adjacent to another settlement on vertex " << v << "." << std::endl;
            return;
        }
    }

    // Ensure there's a valid road leading to the settlement location for subsequent settlements
    if (numCities + numSettlements >= 2) {
        bool hasRoad = false;
        for (const auto &road : myRoads) {
            if ((road.getStart() == vertex || road.getEnd() == vertex) &&
                ((houses[road.getStart()] && houses[road.getStart()]->getOwner() == name) ||
                 (houses[road.getEnd()] && houses[road.getEnd()]->getOwner() == name))) {
                hasRoad = true;
                break;
            }
        }
        if (!hasRoad) {
            std::cerr << "Player must have a road leading to the settlement location." << std::endl;
            return;
        }

        // Check if the player has enough resources
        if (!(wood >= 1 && sheep >= 1 && bricks >= 1 && wheat >= 1)) {
            std::cerr << "Not enough resources to place a settlement." << std::endl;
            return; // Not enough resources to place a settlement
        }
        subtractResource("bricks", 1);
        subtractResource("sheep", 1);
        subtractResource("wood", 1);
        subtractResource("wheat", 1);
    }

    // Find the plots adjacent to the vertex
    std::vector<std::shared_ptr<Plot>> adjacentPlots;
    for (auto &plot : plots) {
        if (std::find(plot->getVertices().begin(), plot->getVertices().end(), vertex) != plot->getVertices().end()) {
            adjacentPlots.push_back(plot);
        }
    }

    // Place the settlement
    auto settlement = std::make_unique<House>(HouseType::Settlement, name, vertex, adjacentPlots);
    House *settlementPtr = settlement.get(); // Get raw pointer before moving

    // Assign raw pointer to the house array
    houses[vertex] = settlementPtr;

    // Move the unique pointer to the Board's unique pointer array to maintain ownership
    board.addHouse(std::move(settlement));

    numSettlements++;
    victoryPoints++;
    std::cout << name << " placed a settlement on vertex " << vertex << "." << std::endl;
    catan.printWinner();

    // Give resources from adjacent plots for the first two settlements
    if (numCities + numSettlements <= 2) {
        for (const auto &plot : settlementPtr->getAdjacentPlots()) {
            addResource(plot->getType(), 1);
        }
    }
}

std::vector<int> Player::getVerticesWithDistanceOne(int sourceVertex, const Board &board) const {
    std::unordered_set<int> adjacentVertices;
    const auto &plots = board.getPlots();

    for (const auto &plot : plots) {
        const auto &vertices = plot->getVertices();
        auto it = std::find(vertices.begin(), vertices.end(), sourceVertex);
        if (it != vertices.end()) {
            auto idx = std::distance(vertices.begin(), it);

            // Previous vertex (if exists)
            if (idx > 0) {
                auto prev_it = std::next(vertices.begin(), idx - 1);
                adjacentVertices.insert(*prev_it);
            }

            // Next vertex (if exists)
            if (idx < static_cast<long>(vertices.size()) - 1) {
                auto next_it = std::next(vertices.begin(), idx + 1);
                adjacentVertices.insert(*next_it);
            }

            // For circular adjacency (if first and last are considered adjacent)
            if (idx == 0 && vertices.size() > 1) {
                auto last_it = std::prev(vertices.end());
                adjacentVertices.insert(*last_it);
            }
            if (idx == static_cast<long>(vertices.size()) - 1 && vertices.size() > 1) {
                auto first_it = vertices.begin();
                adjacentVertices.insert(*first_it);
            }
        }
    }

    return std::vector<int>(adjacentVertices.begin(), adjacentVertices.end());
}

bool Player::placeRoad(int startVertex, int endVertex, Board &board, Player &p1, Player &p2, Player &p3, CatanGame &catan)
{
    if (!isPlayerTurn(catan)) {
        std::cerr << "It's not " << getName() << "'s turn." << std::endl;
        return false;
    }

    // Check if both vertices are within distance one from each other
    std::vector<int> startAdjVertices = getVerticesWithDistanceOne(startVertex, board);
    bool isAdjacent = std::find(startAdjVertices.begin(), startAdjVertices.end(), endVertex) != startAdjVertices.end();

    if (!isAdjacent) {
        std::cout << "The vertices must be within distance one from each other." << std::endl;
        return false;
    }

    // Check if the player has a house on one of the vertices
    auto &houses = board.getMutableHouses();
    bool hasHouseOnStart = houses[startVertex] && houses[startVertex]->getOwner() == name;
    bool hasHouseOnEnd = houses[endVertex] && houses[endVertex]->getOwner() == name;

    if (!hasHouseOnStart && !hasHouseOnEnd)
    {
        std::cout << "Player must have a house on one of the vertices." << std::endl;
        return false;
    }

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
    std::cout << name << " placed a road between " << startVertex << " and " << endVertex << "." << std::endl;
    return true;
}



void Player::buildCity(int vertex, Board &board, CatanGame &catan)
{
    if (!isPlayerTurn(catan)) {
        std::cerr << "It's not " << getName() << "'s turn." << std::endl;
        return;
    }

    auto &houses = board.getMutableHouses();

    // Validate the vertex index
    if (vertex < 0 || vertex >= static_cast<int>(houses.size()))
    {
        std::cerr << "Error: Vertex index " << vertex << " is out of bounds for houses array." << std::endl;
        return;
    }

    // Check if the vertex already has a settlement
    if (!houses[vertex] || houses[vertex]->getOwner() != name || houses[vertex]->getType() != HouseType::Settlement)
    {
        std::cerr << "Error: Cannot build a city on vertex " << vertex << " because it doesn't have your settlement." << std::endl;
        return;
    }

    // Check if the player has enough resources to build a city
    if (!(wheat >= 2 && ore >= 3))
    {
        std::cerr << "Not enough resources to build a city." << std::endl;
        return;
    }

    // Deduct resources for building the city
    subtractResource("wheat", 2);
    subtractResource("ore", 3);

    // Upgrade the settlement to a city
    houses[vertex]->setType(HouseType::City);
    numCities++;
    victoryPoints++;
    std::cout << name << " built a city on vertex " << vertex << "." << std::endl;
    catan.printWinner();
}

void Player::buyDevelopmentCard(Deck &deck, CatanGame &catan)
{
    if (!isPlayerTurn(catan)) {
        std::cerr << "It's not " << getName() << "'s turn." << std::endl;
        return;
    }

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
    }
}

void Player::useDevelopmentCard(DevCardType cardType, Player &p1, Player &p2, Player &p3, CatanGame &catan)
{
    if (!isPlayerTurn(catan)) {
        std::cerr << "It's not " << getName() << "'s turn." << std::endl;
        return;
    }

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
                placeRoad(start1, end1, catan.getBoard(), p1, p2, p3, catan);
                std::cout << "Enter the start and end points for the second road: ";
                std::cin >> start2 >> end2;
                placeRoad(start2, end2, catan.getBoard(), p1, p2, p3, catan);
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
                    catan.printWinner();
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


    bool Player::offerTrade(Player& otherPlayer, const std::string& giveResource, int giveAmount, const std::string& receiveResource, int receiveAmount, CatanGame &catan) {
    if (!isPlayerTurn(catan)) {
        std::cerr << "It's not " << getName() << "'s turn." << std::endl;
        return false;
    }

    // Check if the current player has enough resources to offer the trade
    if (getResourceAmount(giveResource) < giveAmount) {
        std::cerr << "You do not have enough " << giveResource << " to offer the trade." << std::endl;
        return false;
    }

    // Check if the other player has enough resources to accept the trade
    if (otherPlayer.getResourceAmount(receiveResource) < receiveAmount) {
        std::cerr << otherPlayer.getName() << " does not have enough " << receiveResource << " to accept the trade." << std::endl;
        return false;
    }

    // Check if the trade is beneficial for the other player
    if (giveAmount <= receiveAmount) {
        std::cerr << "The trade is not beneficial enough for " << otherPlayer.getName() << "." << std::endl;
        return false;
    }

    // Execute the trade
    subtractResource(giveResource, giveAmount);
    addResource(receiveResource, receiveAmount);
    otherPlayer.subtractResource(receiveResource, receiveAmount);
    otherPlayer.addResource(giveResource, giveAmount);

    std::cout << getName() << " traded " << giveAmount << " " << giveResource << " with " << otherPlayer.getName() << " for " << receiveAmount << " " << receiveResource << "." << std::endl;

    return true;
}

int Player::getKnightCount() const {
    return knightCount;
}
