#include <QCoreApplication>
#include <QtCore>
#include <QDebug>
#include <QFile>
#include <QtXml>
#include <string>
#include "list.h"
#include "graph.h"
#include "queue.h"
#include "basestack.h"
#include <utility>
#include<cctype>

void addEdgesToList(QDomElement item, List &itemlist);
void addVertex(QDomElement item, Vertex &node);
std::string getAirport(char* title, const Graph &graph, std::string airport);
void setGraph(Graph &graph, QDomDocument document);
void DijkstraAlgorithm(const Graph &unvisited, const std::string& airport_i, std::string airport_f, char ans);
std::string CorrectACode(const Graph &graph, string airport);
bool getRoute(baseStack<std::string>& route, std::string airport_f, std::string airport_i, vector<pair<Vertex, Vertex> > nodePrev);
void print(baseStack<std::string>& route, const Graph& unvisited, bool foundRoute);
bool getRepeat();
char choice();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QFile file("output.xml");
    QDomDocument document;
    Graph unvisited;
    std::string airport_i, airport_f;

    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug() <<"Failed to open file";
        return -1;
    }
    else
    {
        if(!document.setContent(&file))
        {
            qDebug()<<"Failed to load document";
            return -1;
        }
        file.close();
    }

    setGraph(unvisited, document);
    do
    {
        std::cout << "\n\n\nWELCOME!!\n\n";
        airport_i = getAirport("Please input your initial airport: ", unvisited, "");
        airport_f = getAirport("Please input your destination airport: ", unvisited, airport_i);

        airport_i = CorrectACode(unvisited, airport_i);
        airport_f = CorrectACode(unvisited, airport_f);

        char ans = choice();
        DijkstraAlgorithm(unvisited,airport_i, airport_f, ans);
    }while(getRepeat());
    return 0;
}

bool getRepeat()
{
    char input;
    std::cout<<"Do you wish to input another airport?\nPress y for yes anything else for no"<<std::endl;
    std::cin>>input;
    return toupper(input) == 'Y';
}

std::string getAirport(char* title, const Graph &graph, std::string airport)
{
    bool airportExist = false;
    std::string input;

    while (!airportExist)
    {
        std::cout << title;
        std::cin >> input;
        for (int i=0; i<input.length(); ++i)
            input[i] = toupper(input[i]);
        if (input == airport)
            std::cout << "Invalid Airport. Please input another airport.\n" ;
        else
        {
            for (int i=0; !airportExist && i<graph.graphSize(); ++i)
                if (input == graph.getgraphIndex(i).theVertex().theACode1() || input == graph.getgraphIndex(i).theVertex().theACode2())
                    airportExist = true;
            if (!airportExist)
                qDebug("Not a valid airport");
        }
    }
    return input;
}

void setGraph(Graph &graph, QDomDocument document)
{
    List vertexList;
    Vertex tempVertex;
    QDomElement root = document.firstChildElement();
    QDomNodeList items = root.elementsByTagName("Vertex");

    for(int i = 0; i < items.count(); ++i)
    {
        QDomNode itemNode = items.at(i);
        if(itemNode.isElement());
        {
            QDomElement item = itemNode.toElement();
            addVertex(item,tempVertex);
            vertexList.theVertex() = tempVertex;
            addEdgesToList(item,vertexList);
            graph.insertVertex(vertexList);
        }
        vertexList.clear();
    }
}

void addVertex(QDomElement item, Vertex& node)
{
    std::string city = item.attribute("City").toStdString();
    std::string airportCode1 = item.attribute("IATA").toStdString();
    std::string airportCode2 = item.attribute("ICAO").toStdString();
    std::string country = item.attribute("Country").toStdString();

    node.theACode1() = airportCode1;
    node.theACode2() = airportCode2;
    node.theCity() = city;
    node.theCountry() = country;
}

void addEdgesToList(QDomElement item, List& itemlist)
{
    QDomNodeList items = item.elementsByTagName("Edge");
    std::string destination, airline;
    double distance;

    for(int i = 0; i < items.count(); ++i)
    {
        QDomNode itemnode = items.at(i);
        if(itemnode.isElement())
        {
            QDomElement itemele = itemnode.toElement();
            destination = itemele.attribute("Destination").toStdString();
            airline = itemele.attribute("Carrier").toStdString();
            distance = itemele.attribute("Distance").toDouble();
        }
        itemlist.addEdge(Edge(distance,airline,destination));
    }
}

std::string CorrectACode(const Graph &graph,  std::string airport)
{
    bool repeat = true;

    while(repeat)
    {
        if (airport.length() > 3)
        {
            for (int i=0; i<graph.graphSize(); ++i)
                if (airport == graph.getgraphIndex(i).theVertex().theACode2())
                {
                    if(graph.getgraphIndex(i).theVertex().theACode1() == "")
                    {
                        std::cout<<"No possible routes to this location."<<std::endl<<"Please input another airport: ";
                        std::cin>>airport;
                    }
                    else
                        return graph.getgraphIndex(i).theVertex().theACode1();
                }
        }
        else
            return airport;
    }
}

void DijkstraAlgorithm(const Graph &unvisited, const string& airport_i, string airport_f, char ans)
{
    pQueue<List,double> queue;
    double distance, zero = 0, infinite = 50000;
    vector<pair<Vertex,double> > nodeDist;
    vector<pair<Vertex,Vertex> > nodePrev;
    List tempList = unvisited.getList(airport_i);
    Vertex undefined,tempVertex = tempList.theVertex();
    baseStack<std::string> route;
    bool foundRoute;

    nodeDist.push_back(make_pair(tempVertex, zero));
    nodePrev.push_back(make_pair(tempVertex,undefined));
    queue.enqueue(tempList, zero);
    for (int i=0;i<unvisited.graphSize(); ++i)
    {
        if (unvisited.getgraphIndex(i).theVertex().theACode1() != airport_i && unvisited.getgraphIndex(i).theVertex().theACode1()!= "" )
        {
            nodeDist.push_back(make_pair(unvisited.getgraphIndex(i).theVertex(),infinite));
            nodePrev.push_back(make_pair(unvisited.getgraphIndex(i).theVertex(),undefined));
        }
        queue.enqueue(unvisited.getgraphIndex(i),infinite);
    }
    while(!queue.empty())
    {
        tempList = queue.front();
        queue.dequeue();
        if(tempList.getVertex().theACode1()== airport_f)
            break;
        for (int i=0; i<tempList.getTotalEdges(); ++i)
        {
            for (int j=0; j < nodeDist.size(); ++j)
            {
                if(nodeDist[j].first.theACode1() == tempList.theVertex().theACode1())
                {
                    if (ans == 'A')
                        distance = nodeDist[j].second + tempList.theEdge(i).getDistance();
                    else
                        distance = nodeDist[j].second;
                    break;
                }
            }
            for (int j=0; j<nodeDist.size(); ++j)
            {
                if (nodeDist[j].first.theACode1() == tempList.theEdge(i).getDestination())
                {
                    if (distance < nodeDist[j].second)
                    {
                        nodeDist[j].second = distance;
                        nodePrev[j].second = tempList.theVertex();
                        queue.decreasePriority(unvisited.getList(tempList.theEdge(i).getDestination()), distance);
                    }
                }
            }
        }
    }
    foundRoute = getRoute(route,airport_f,airport_i,nodePrev);
    print(route, unvisited,foundRoute);
}

void print(baseStack<std::string>& route, const Graph& unvisited, bool foundRoute)
{
    double distance;
    std::string a1, a2;
    if(foundRoute)
    {
        distance = 0;
        std::cout << "\n\nYour route is: \n\n";
        while (route.size() > 1)
        {
            a1=route.top();
            route.pop();
            a2=route.top();

            std::cout << "Depart " << a1 << " (" << unvisited.getList(a1).theVertex().theCity() << ", "<<unvisited.getList(a1).theVertex().theCountry() << ") via ";
            for (int i=0; i<unvisited.getList(a1).getTotalEdges();++i)
            {
                if (unvisited.getList(a1).theEdge(i).getDestination() == a2)
                {
                    std::cout << "[";
                    for (int j=0; j<unvisited.getList(a1).theEdge(i).getNumberOfCarriers()-1;++j)
                        std::cout << unvisited.getList(a1).theEdge(i).getCarrier(j) << ", or ";
                    std::cout << unvisited.getList(a1).theEdge(i).getCarrier(unvisited.getList(a1).theEdge(i).getNumberOfCarriers()-1)
                              <<"] and fly " << unvisited.getList(a1).theEdge(i).getDistance() << " km to "<< a2 <<".\n";
                    distance += unvisited.getList(a1).theEdge(i).getDistance();
                    break;
                }
            }
        }
        std::cout << "Arrive at " << a2 << " (" << unvisited.getList(a2).theVertex().theCity() << ", "<<unvisited.getList(a2).theVertex().theCountry() << ").\n";
        std::cout << "\nTotal distance is: " << distance << " km.\n\n\n";
    }
    else
        std::cout<<"No possible route to location\n\n"<<std::endl;
}

bool getRoute(baseStack<std::string>& route, std::string airport_f, std::string airport_i, vector<pair<Vertex,Vertex> > nodePrev)
{
    bool repeat=true;
    route.push(airport_f);
    while (repeat)
    {
        for (int i=0; i<nodePrev.size(); ++i)
        {
            if (nodePrev[i].first.theACode1() == airport_f)
            {
                route.push(nodePrev[i].second.theACode1());
                airport_f = nodePrev[i].second.theACode1();
                if (airport_f == airport_i)
                    repeat = false;
                else if(airport_f == "")
                    return false;
                break;
            }
        }
    }
    return true;
}

char choice()
{
    char ans;
    bool notValid = true;
    while(notValid)
    {
        std::cout << "\n\nPlease choose you options:\n"
                  << "    A. Shortest route based on distance\n"
                  << "    B. Shortest route based on number of stops\nOPTION: ";
        cin >> ans;
        ans = toupper(ans);
        if (ans != 'A' && ans != 'B')
        {
            std::cout << "Invalid option. Please try again.\n";
            notValid = true;
        }
        else
            notValid = false;
    }

    return ans;
}
