//asaf0604@gmail.com 325362457
#pragma once
#include <string>

class Road {
public:
    Road(int start, int end, const std::string& owner);
    int getStart() const;
    int getEnd() const;
    std::string getOwner() const;
    bool operator<(const Road& other) const;
    bool operator==(const Road &other) const;

private:
    int start;
    int end;
    std::string owner;
};
