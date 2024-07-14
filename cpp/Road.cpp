// asaf0604@gmail.com 325362457
#include "Road.hpp"

Road::Road(int start, int end, const std::string &owner) : owner(owner)
{
    if (start < end)
    {
        this->start = start;
        this->end = end;
    }
    else
    {
        this->start = end;
        this->end = start;
    }
}

int Road::getStart() const
{
    return start;
}

int Road::getEnd() const
{
    return end;
}

std::string Road::getOwner() const
{
    return owner;
}

bool Road::operator<(const Road &other) const
{
    if (start < other.start)
    {
        return true;
    }
    else if (start == other.start)
    {
        return end < other.end;
    }
    return false;
}

bool Road::operator==(const Road &other) const
{
    return start == other.start && end == other.end && owner == other.owner;
}