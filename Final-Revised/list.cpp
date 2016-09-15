#include "list.h"

List::List()
{
    nukem();
}

List::~List()
{
    nukem();
}

List::List(const List& other)
{
    copy(other);
}

List List::operator=(const List& other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

Vertex& List::theVertex()
{
    return node;
}

void List::addEdge(const Edge& item)
{
    int size = edges.size();
    std::string stop = item.getDestination();

    for(int i = 0; i < size; ++i)
    {
        if(edges[i].getDestination() == stop)
        {
            edges[i].setCarrier(item.getCarrier(0));
            return;
        }
    }
    edges.push_back(item);
}

void List::clear()
{
    edges.clear();
}

Edge& List::theEdge(const int &index)
{
    return edges[index];
}

int List::getTotalEdges()
{
    return edges.size();
}

void List::nukem()
{
    node = prev = Vertex();
    edges.clear();
    dist = 50000;
}

void List::copy(const List& other)
{
    node = other.node;
    edges = other.edges;
    dist = other.dist;
    prev = other.prev;
}

std::ostream& operator<<(std::ostream& out, List item)
{
    out << item.theVertex().theACode1();
    return out;
}

Vertex List::getVertex() const
{
    return node;
}

bool operator == (const List& l_1, const List& l_2)
{
    return l_1.getVertex().theACode1() == l_2.getVertex().theACode1();
}

double& List::theDist()
{
    return dist;
}

Vertex& List::thePrev()
{
    return prev;
}
