#ifndef PLOT_HPP
#define PLOT_HPP

#include <string>
#include <vector>
#include <memory>
#include <set>

class Plot {
public:
    Plot(const std::string& type, int number);

    std::string getType() const;
    void setType(const std::string& type);

    int getNumber() const;
    void setNumber(int number);

    std::vector<std::shared_ptr<Plot>> getNeighbors() const;
    void addNeighbor(const std::shared_ptr<Plot>& neighbor);

    std::set<int> getVertices() const;  // Ensure this method is correctly defined
    void setVertices(const std::set<int>& vertices);

private:
    std::string type;
    int number;
    std::vector<std::shared_ptr<Plot>> neighbors;
    std::set<int> vertices;
};

#endif // PLOT_HPP
