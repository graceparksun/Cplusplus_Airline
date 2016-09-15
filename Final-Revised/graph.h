#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include "edge.h"
#include "vertex.h"
#include "list.h"

class Graph
{
    public:
        Graph();
        ~Graph();
        Graph(const Graph& other);
        Graph operator=(const Graph& other);

        void insertVertex(const List& item);
        int graphSize() const;

        int getTotalEdges();
        List getgraphIndex(const int &index) const;

        List getList(const std::string& airport) const;

        friend
        std::ostream& operator<<(std::ostream& out, Graph item);

    private:
        std::vector<List> graph;

        void nukem();
        void copy(const Graph& other);
};

#endif // GRAPH_H
