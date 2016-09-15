#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <vector>
#include "edge.h"
#include "vertex.h"

class List
{
    public:
        List();
        ~List();
        List(const List& other);
        List operator=(const List& other);

        Vertex& theVertex();

        void clear();
        void addEdge(const Edge& item);
        Edge& theEdge(const int &index);
        int getTotalEdges();
        Vertex getVertex() const;

        friend
        bool operator == (const List& l_1, const List& l_2);

        friend
        std::ostream& operator<<(std::ostream& out, List item);

        double& theDist();
        Vertex& thePrev();

    private:
        Vertex node, prev;
        std::vector<Edge> edges;
        double dist;

        void nukem();
        void copy(const List& other);
};

#endif // LIST_H
