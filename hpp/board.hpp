#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <vector>
#include <memory>
#include "Plot.hpp"
#include "Houses.hpp"

class Board {
public:
    static constexpr int NUM_VERTICES = 53; // Declare the number of vertices

    Board();
    void createBoard();
    void setNeighbors();
    const std::array<std::shared_ptr<Plot>, 19>& getPlots() const;
    const std::array<House*, NUM_VERTICES>& getHouses() const;
    std::array<House*, NUM_VERTICES>& getMutableHouses();
    std::array<std::shared_ptr<Plot>, 19>& getMutablePlots();
    void addHouse(std::unique_ptr<House> house);

private:
    std::array<std::shared_ptr<Plot>, 19> plots;
    std::array<House*, NUM_VERTICES> houses;
    std::vector<std::unique_ptr<House>> houseOwnership; // To maintain ownership
};

#endif // BOARD_HPP
