#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <vector>
#include <string>

class Edge
{
    public:
        Edge();
        Edge(double kilometers, std::string airline, std::string destinationCode);
        ~Edge();
        Edge(const Edge& other);
        Edge operator=(const Edge& other);

        void setDistance(double kilometers);
        double getDistance();

        void setDestination(std::string destinationCode);
        std::string getDestination() const;

        int getNumberOfCarriers();
        std::string getCarrier(int index) const;
        void setCarrier(std::string airline);

        friend
        std::ostream& operator<<(std::ostream& out, Edge item);

    private:
        double distance;
        std::vector<std::string> carriers;
        std::string destination;

        void nukem();
        void copy(const Edge& other);
};

#endif // EDGE_H
