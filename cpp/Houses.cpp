#include "Houses.hpp"
#include "Plot.hpp"

House::House(HouseType type, const std::string& owner, std::array<std::shared_ptr<Plot>, 3> adjacentPlots)
    : type(type), owner(owner), adjacentPlots(adjacentPlots) {}

HouseType House::getType() const {
    return type;
}

void House::setType(HouseType type) {
    this->type = type;
}

std::string House::getOwner() const {
    return owner;
}

void House::setOwner(const std::string& owner) {
    this->owner = owner;
}

const std::array<std::shared_ptr<Plot>, 3>& House::getAdjacentPlots() const {
    return adjacentPlots;
}
