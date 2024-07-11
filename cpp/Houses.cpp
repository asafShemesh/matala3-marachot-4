#include "Houses.hpp"

House::House(HouseType type, const std::string& owner) : type(type), owner(owner) {}

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
