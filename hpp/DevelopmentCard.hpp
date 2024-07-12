#pragma once
#include <string>

enum class DevCardType { Monopoly, RoadBuilding, YearOfPlenty, Knight, VictoryPoint };

class DevelopmentCard {
public:
    virtual ~DevelopmentCard() = default;
    virtual DevCardType getType() const = 0;
};

class MonopolyCard : public DevelopmentCard {
public:
    DevCardType getType() const override { return DevCardType::Monopoly; }
};

class RoadBuildingCard : public DevelopmentCard {
public:
    DevCardType getType() const override { return DevCardType::RoadBuilding; }
};

class YearOfPlentyCard : public DevelopmentCard {
public:
    DevCardType getType() const override { return DevCardType::YearOfPlenty; }
};

class KnightCard : public DevelopmentCard {
public:
    DevCardType getType() const override { return DevCardType::Knight; }
};

class VictoryPointCard : public DevelopmentCard {
public:
    DevCardType getType() const override { return DevCardType::VictoryPoint; }
};
