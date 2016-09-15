#include "edge.h"

Edge::Edge()
{
    nukem();
}

Edge::~Edge()
{
    nukem();
}

Edge::Edge(double kilometers, std::string airline, std::string destinationCode)
{
    distance = kilometers;
    carriers.push_back(airline);
    destination = destinationCode;
}

Edge::Edge(const Edge& other)
{
    copy(other);
}

Edge Edge::operator=(const Edge& other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

void Edge::nukem()
{
    distance = 0;
    carriers.clear();
    destination = "";
}

void Edge::copy(const Edge& other)
{
    distance = other.distance;
    carriers = other.carriers;
    destination = other.destination;
}

void Edge::setDistance(double kilometers)
{
    distance = kilometers;
}

double Edge::getDistance()
{
    return distance;
}

void Edge::setDestination(std::string destinationCode)
{
    destination = destinationCode;
}

std::string Edge::getDestination() const
{
    return destination;
}

int Edge::getNumberOfCarriers()
{
    return carriers.size();
}

std::string Edge::getCarrier(int index) const
{
    return carriers[index];
}

void Edge::setCarrier(std::string airline)
{
    carriers.push_back(airline);
}

std::ostream& operator<<(std::ostream& out, Edge item)
{
    out<<item.distance<<" "<<item.getDestination()<<" ";
    for(int i = 0; i< item.carriers.size(); ++i)
        out<<item.carriers[i]<<" ";
    return out;
}
