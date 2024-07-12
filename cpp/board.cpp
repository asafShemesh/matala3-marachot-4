#include "board.hpp"

Board::Board() {
    createBoard();
}

void Board::createBoard() {
    plots = {
        std::make_shared<Plot>("Sheep", 5), std::make_shared<Plot>("Ore", 3),
        std::make_shared<Plot>("Wheat", 3), std::make_shared<Plot>("Wood", 8),
        std::make_shared<Plot>("Wheat", 9), std::make_shared<Plot>("Wood", 10),
        std::make_shared<Plot>("Desert", 0), std::make_shared<Plot>("Wheat", 5),
        std::make_shared<Plot>("Brick", 4), std::make_shared<Plot>("Sheep", 4),
        std::make_shared<Plot>("Ore", 8), std::make_shared<Plot>("Sheep", 2),
        std::make_shared<Plot>("Wood", 6), std::make_shared<Plot>("Wheat", 11),
        std::make_shared<Plot>("Sheep", 9), std::make_shared<Plot>("Brick", 12),
        std::make_shared<Plot>("Brick", 11), std::make_shared<Plot>("Wood", 6),
        std::make_shared<Plot>("Ore", 10)
    };

    houses.fill(nullptr);  // Initialize the houses array with nullptr

    setNeighbors();
}

void Board::setNeighbors() {
    // Setting up neighbors based on the specific Catan layout in the image
    plots[0]->addNeighbor(plots[1]);
    plots[0]->addNeighbor(plots[3]);
    plots[0]->addNeighbor(plots[4]);

    plots[1]->addNeighbor(plots[0]);
    plots[1]->addNeighbor(plots[2]);
    plots[1]->addNeighbor(plots[4]);
    plots[1]->addNeighbor(plots[5]);

    plots[2]->addNeighbor(plots[1]);
    plots[2]->addNeighbor(plots[5]);
    plots[2]->addNeighbor(plots[6]);

    plots[3]->addNeighbor(plots[0]);
    plots[3]->addNeighbor(plots[4]);
    plots[3]->addNeighbor(plots[7]);
    plots[3]->addNeighbor(plots[8]);

    plots[4]->addNeighbor(plots[0]);
    plots[4]->addNeighbor(plots[1]);
    plots[4]->addNeighbor(plots[3]);
    plots[4]->addNeighbor(plots[5]);
    plots[4]->addNeighbor(plots[8]);
    plots[4]->addNeighbor(plots[9]);

    plots[5]->addNeighbor(plots[1]);
    plots[5]->addNeighbor(plots[2]);
    plots[5]->addNeighbor(plots[4]);
    plots[5]->addNeighbor(plots[6]);
    plots[5]->addNeighbor(plots[9]);
    plots[5]->addNeighbor(plots[10]);

    plots[6]->addNeighbor(plots[2]);
    plots[6]->addNeighbor(plots[5]);
    plots[6]->addNeighbor(plots[10]);
    plots[6]->addNeighbor(plots[11]);

    plots[7]->addNeighbor(plots[3]);
    plots[7]->addNeighbor(plots[8]);
    plots[7]->addNeighbor(plots[12]);

    plots[8]->addNeighbor(plots[3]);
    plots[8]->addNeighbor(plots[4]);
    plots[8]->addNeighbor(plots[7]);
    plots[8]->addNeighbor(plots[9]);
    plots[8]->addNeighbor(plots[12]);
    plots[8]->addNeighbor(plots[13]);

    plots[9]->addNeighbor(plots[4]);
    plots[9]->addNeighbor(plots[5]);
    plots[9]->addNeighbor(plots[8]);
    plots[9]->addNeighbor(plots[10]);
    plots[9]->addNeighbor(plots[13]);
    plots[9]->addNeighbor(plots[14]);

    plots[10]->addNeighbor(plots[5]);
    plots[10]->addNeighbor(plots[6]);
    plots[10]->addNeighbor(plots[9]);
    plots[10]->addNeighbor(plots[11]);
    plots[10]->addNeighbor(plots[14]);
    plots[10]->addNeighbor(plots[15]);

    plots[11]->addNeighbor(plots[6]);
    plots[11]->addNeighbor(plots[10]);
    plots[11]->addNeighbor(plots[15]);

    plots[12]->addNeighbor(plots[7]);
    plots[12]->addNeighbor(plots[8]);
    plots[12]->addNeighbor(plots[13]);
    plots[12]->addNeighbor(plots[16]);

    plots[13]->addNeighbor(plots[8]);
    plots[13]->addNeighbor(plots[9]);
    plots[13]->addNeighbor(plots[12]);
    plots[13]->addNeighbor(plots[14]);
    plots[13]->addNeighbor(plots[16]);
    plots[13]->addNeighbor(plots[17]);

    plots[14]->addNeighbor(plots[9]);
    plots[14]->addNeighbor(plots[10]);
    plots[14]->addNeighbor(plots[13]);
    plots[14]->addNeighbor(plots[15]);
    plots[14]->addNeighbor(plots[17]);
    plots[14]->addNeighbor(plots[18]);

    plots[15]->addNeighbor(plots[10]);
    plots[15]->addNeighbor(plots[11]);
    plots[15]->addNeighbor(plots[14]);
    plots[15]->addNeighbor(plots[18]);

    plots[16]->addNeighbor(plots[12]);
    plots[16]->addNeighbor(plots[13]);
    plots[16]->addNeighbor(plots[17]);

    plots[17]->addNeighbor(plots[13]);
    plots[17]->addNeighbor(plots[14]);
    plots[17]->addNeighbor(plots[16]);
    plots[17]->addNeighbor(plots[18]);

    plots[18]->addNeighbor(plots[14]);
    plots[18]->addNeighbor(plots[15]);
    plots[18]->addNeighbor(plots[17]);
}

std::array<std::shared_ptr<Plot>, Board::NUM_PLOTS>& Board::getPlots() {
    return plots;
}

const std::array<House*, Board::NUM_PLOTS>& Board::getHouses() const { 
    return houses;
}

void Board::addHouse(std::unique_ptr<House> house) {
    houseOwnership.push_back(std::move(house));
}

std::array<House*, Board::NUM_PLOTS>& Board::getMutableHouses() {
    return houses;
}