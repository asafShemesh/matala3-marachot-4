#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <memory>
#include "Plot.hpp"
#include "Houses.hpp"

class Board {
public:
    static const int NUM_PLOTS = 19;

    Board();

    void createBoard();
    void setNeighbors();

    const std::array<std::shared_ptr<Plot>, 19>& getPlots() const;
    const std::array<House*, NUM_PLOTS>& getHouses() const;
    void addHouse(std::unique_ptr<House> house);
    std::array<House*, NUM_PLOTS>& getMutableHouses();
    std::array<std::shared_ptr<Plot>, NUM_PLOTS>& getMutablePlots();  // Add this line

private:
    std::array<std::shared_ptr<Plot>, NUM_PLOTS> plots;
    std::array<House*, NUM_PLOTS> houses;
    std::vector<std::unique_ptr<House>> houseOwnership;
};

#endif // BOARD_HPP
