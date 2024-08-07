// asaf0604@gmail.com 325362457
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <ostream>
#include <set>
#include <algorithm>

enum class HouseType
{
    Settlement,
    City
};

class Plot;

class House
{
public:
    House(HouseType type, const std::string &owner, int vertex, std::vector<std::shared_ptr<Plot>> adjacentPlots);
    HouseType getType() const;
    void setType(HouseType type);
    std::string getOwner() const;
    void setOwner(const std::string &owner);
    const std::vector<std::shared_ptr<Plot>> &getAdjacentPlots() const;
    int getVertex() const;

private:
    HouseType type;
    std::string owner;
    int vertex;
    std::vector<std::shared_ptr<Plot>> adjacentPlots;
};
