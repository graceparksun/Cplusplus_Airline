#include "graph.h"

Graph::Graph()
{
    nukem();
}

Graph::~Graph()
{
    nukem();
}

Graph::Graph(const Graph& other)
{
    copy(other);
}

Graph Graph::operator=(const Graph& other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

void Graph::nukem()
{
    graph.clear();
}

void Graph::copy(const Graph& other)
{
    graph = other.graph;
}

void Graph::insertVertex(const List& item)
{
    graph.push_back(item);
}

int Graph::getTotalEdges()
{
    return graph[0].getTotalEdges();
}


int Graph::graphSize() const
{
    return graph.size();
}


List Graph::getgraphIndex(const int &index) const
{
    return graph[index];
}

List Graph::getList(const std::string& airport) const
{
    for (int i=0; i<graph.size();++i)
    {
        if(airport == graph[i].getVertex().theACode1())
            return graph[i];
    }
}

std::ostream& operator<<(std::ostream& out, Graph item)
{
    for(int i = 0; i < item.graph.size(); ++i)
        for(int j = 0; j < item.graph[i].getTotalEdges();++j)
            out<<item.graph[i].theEdge(j)<<std::endl;
    return out;
}
