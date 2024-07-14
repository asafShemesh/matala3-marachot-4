// asaf0604@gmail.com 325362457
#include "Houses.hpp"
#include "Plot.hpp"

House::House(HouseType type, const std::string &owner, int vertex, std::vector<std::shared_ptr<Plot>> adjacentPlots)
    : type(type), owner(owner), vertex(vertex), adjacentPlots(std::move(adjacentPlots))
{
}

HouseType House::getType() const
{
    return type;
}

void House::setType(HouseType type)
{
    this->type = type;
}

std::string House::getOwner() const
{
    return owner;
}

void House::setOwner(const std::string &owner)
{
    this->owner = owner;
}

const std::vector<std::shared_ptr<Plot>> &House::getAdjacentPlots() const
{
    return adjacentPlots;
}

int House::getVertex() const
{
    return vertex;
}
