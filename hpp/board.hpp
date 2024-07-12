#pragma once
#include <array>
#include <memory>
#include <vector>
#include "Plot.hpp"
#include "Houses.hpp"

class Board {
public:
    static const int NUM_PLOTS = 19;
    Board();
    void createBoard();
    void setNeighbors();
    std::array<std::shared_ptr<Plot>, NUM_PLOTS>& getPlots();
    const std::array<House*, NUM_PLOTS>& getHouses() const;
    std::array<House*, NUM_PLOTS>& getMutableHouses(); // Added mutable version
    void addHouse(std::unique_ptr<House> house);
    

private:
    std::array<std::shared_ptr<Plot>, NUM_PLOTS> plots;
    std::array<House*, NUM_PLOTS> houses;
    std::vector<std::unique_ptr<House>> houseOwnership;
};
