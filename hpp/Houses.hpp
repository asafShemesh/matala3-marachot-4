#pragma once
#include <string>
#include <array>
#include <memory>

enum class HouseType { Settlement, City };

class Plot; // Forward declaration

class House {
public:
    House(HouseType type, const std::string& owner, std::array<std::shared_ptr<Plot>, 3> adjacentPlots);
    HouseType getType() const;
    void setType(HouseType type);
    std::string getOwner() const;
    void setOwner(const std::string& owner);
    const std::array<std::shared_ptr<Plot>, 3>& getAdjacentPlots() const;

private:
    HouseType type;
    std::string owner;
    std::array<std::shared_ptr<Plot>, 3> adjacentPlots;
};
