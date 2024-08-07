// asaf0604@gmail.com 325362457
#include "Plot.hpp"

Plot::Plot(const std::string &type, int number) : type(type), number(number) {}

std::string Plot::getType() const
{
    return type;
}

void Plot::setType(const std::string &type)
{
    this->type = type;
}

int Plot::getNumber() const
{
    return number;
}

void Plot::setNumber(int number)
{
    this->number = number;
}

std::vector<std::shared_ptr<Plot>> Plot::getNeighbors() const
{
    return neighbors;
}

void Plot::addNeighbor(const std::shared_ptr<Plot> &neighbor)
{
    neighbors.push_back(neighbor);
}

void Plot::setVertices(const std::vector<int> &vertices)
{
    this->vertices = vertices;
}

const std::vector<int> &Plot::getVertices() const
{
    return vertices;
}
