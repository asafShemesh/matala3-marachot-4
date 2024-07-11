#pragma once
#include <string>
#include <vector>
#include <memory>

class Plot {
public:
    Plot(const std::string& type, int number);

    std::string getType() const;
    void setType(const std::string& type);

    int getNumber() const;
    void setNumber(int number);

    std::vector<std::shared_ptr<Plot>> getNeighbors() const;
    void addNeighbor(const std::shared_ptr<Plot>& neighbor);

private:
    std::string type;
    int number;
    std::vector<std::shared_ptr<Plot>> neighbors;
};
