#pragma once
#include <string>

enum class DevCardType {
    Monopoly,
    RoadBuilding,
    YearOfPlenty,
    Knight,
    VictoryPoint
};

class DevCard {
public:
    virtual DevCardType getType() const = 0;
    virtual ~DevCard() = default;
};

class MonopolyCard : public DevCard {
public:
    DevCardType getType() const override { return DevCardType::Monopoly; }
};

class RoadBuildingCard : public DevCard {
public:
    DevCardType getType() const override { return DevCardType::RoadBuilding; }
};

class YearOfPlentyCard : public DevCard {
public:
    DevCardType getType() const override { return DevCardType::YearOfPlenty; }
};

class KnightCard : public DevCard {
public:
    DevCardType getType() const override { return DevCardType::Knight; }
};

class VictoryPointCard : public DevCard {
public:
    DevCardType getType() const override { return DevCardType::VictoryPoint; }
};
