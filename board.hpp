#pragma once
#include <array>
#include <memory>
#include "Plot.hpp"

class Board {
public:
    static constexpr int NUM_PLOTS = 19;
    Board();
    void createBoard();
    std::array<std::shared_ptr<Plot>, NUM_PLOTS> getPlots() const;
private:
    std::array<std::shared_ptr<Plot>, NUM_PLOTS> plots;
    void setNeighbors();
};
