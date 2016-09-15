#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <string>

class Vertex
{
    public:
        Vertex();
        Vertex(const std::string &town, const std::string &airport1, const std::string &airport2, const std::string county);
        ~Vertex();
        Vertex(const Vertex& other);
        Vertex operator=(const Vertex& other);

        std::string& theCity();
        std::string& theACode1();
        std::string& theACode2();
        std::string& theCountry();

        friend
        std::ostream& operator<<(std::ostream& out, const Vertex& item);

    private:
        std::string city, country, ACode1, ACode2;

        void nukem();
        void copy(const Vertex& other);
};

#endif // VERTEX_H
