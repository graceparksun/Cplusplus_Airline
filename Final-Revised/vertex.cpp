#include "vertex.h"

Vertex::Vertex()
{
    nukem();
}

Vertex::~Vertex()
{
    nukem();
}

Vertex::Vertex(const std::string &town, const std::string &airport1, const std::string &airport2, const std::string county)
{
    city = town;
    ACode1 = airport1;
    ACode2 = airport2;
    country = county;
}

Vertex::Vertex(const Vertex& other)
{
    copy(other);
}

Vertex Vertex::operator=(const Vertex& other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

void Vertex::nukem()
{
    city = ACode1 = ACode2 = country = "";
}

void Vertex::copy(const Vertex& other)
{
    city = other.city;
    ACode1 = other.ACode1;
    ACode2 = other.ACode2;
    country = other.country;
}

std::string& Vertex::theCity()
{
    return city;
}

std::string& Vertex::theACode1()
{
    return ACode1;
}

std::string& Vertex::theACode2()
{
    return ACode2;
}

std::string& Vertex::theCountry()
{
    return country;
}

std::ostream& operator<<(std::ostream& out, const Vertex& item)
{
    out<<"Airport Code 1: "<<item.ACode1<< " Airport Code 2: " <<item.ACode2 <<" City: "<<item.city<<" Country: "<<item.country<<std::endl;
    return out;
}
