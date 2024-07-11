#pragma once
#include <string>

enum class HouseType { Settlement, City };

class House {
public:
    House(HouseType type, const std::string& owner);
    HouseType getType() const;
    void setType(HouseType type);
    std::string getOwner() const;
    void setOwner(const std::string& owner);
private:
    HouseType type;
    std::string owner;
};
