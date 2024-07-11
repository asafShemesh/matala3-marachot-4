#pragma once
#include <array>
#include <memory>
#include "Plot.hpp"
#include "Houses.hpp"

class Board {
public:
    static constexpr int NUM_PLOTS = 19;
    Board();
    void createBoard();
    std::array<std::shared_ptr<Plot>, NUM_PLOTS> getPlots() const;
    std::array<std::unique_ptr<House>, NUM_PLOTS>& getHouses();
    const std::array<std::unique_ptr<House>, NUM_PLOTS>& getHouses() const;

private:
    std::array<std::shared_ptr<Plot>, NUM_PLOTS> plots;
    std::array<std::unique_ptr<House>, NUM_PLOTS> houses;
    void setNeighbors();
};
