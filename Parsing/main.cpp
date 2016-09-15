#include <QCoreApplication>
#include <QtCore>
#include <QDebug>
#include <QtXml>
#include <fstream>
#include <cstdio>
#include<cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdlib>


double DegToRad(const double& deg);
double calculateDistance(double lat1,double lat2, double long1,double long2);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QDomDocument document;
    QFile file("output.xml");
    QDomElement root = document.createElement("Airport");
    std::ifstream input, routes, edgeLocation, airlineInfo;
    std::string information, city, latitude, latitude2, longitude2, longitude, airportCode,airportCodeTemp, airline, destination,temp,orgin, informationMore ,tempTwo;
    int index = 0, routeIndex = 0, count = 0, edgeCount = 0, commaIndex = 0;
    std::string country;
    double distance = 0;
    char junk;
    int total = 0;
    input.open("airports-1.dat");
    routes.open("routes.dat");
    edgeLocation.open("airports.dat");
    airlineInfo.open("airline.dat");
    document.appendChild(root);
    std::string icaoCode;

    while(std::getline(input,information, ','))
    {
        if(index == 1)
        {
            input>>junk;
            std::getline(input,city,'"');
        }
        else if(index == 2)
        {
            input>>junk;
            std::getline(input,country,'"');
        }
        else if(index == 3)
        {
            input>>junk;
            getline(input,airportCode,'"');
        }
        else if(index == 4)
        {
            input>>junk;
            getline(input,icaoCode,',');
            ++index;
            icaoCode.erase(icaoCode.length()-1,1);
        }
        else if(index == 6)
            latitude = information;
        else if(index == 7)
        {
            std::cout<<++total<<std::endl;
            longitude = information;
            QDomElement node = document.createElement("Vertex");
            node.setAttribute("IATA",QString::fromStdString(airportCode));
            node.setAttribute("City",QString::fromStdString(city));
            node.setAttribute("ICAO",QString::fromStdString(icaoCode));
            node.setAttribute("Country",QString::fromStdString(country));
            root.appendChild(node);

            while(getline(routes,information))
            {
                routeIndex = information.find_first_of(',');
                airline = information.substr(0,routeIndex);
                temp = information.substr(routeIndex+1);
                while(routeIndex != std::string::npos)
                {
                    routeIndex = temp.find_first_of(',');
                    temp = temp.substr(routeIndex+1);
                    ++count;
                    if(count == 1)
                    {
                        orgin = temp.substr(0,3);
                        if(orgin != airportCode)
                            break;
                    }
                    else if(count == 3)
                    {
                        destination = temp.substr(0,3);
                        while(std::getline(edgeLocation,informationMore))
                        {
                            edgeCount = 1;
                            commaIndex = informationMore.find_first_of(',');
                            tempTwo = informationMore.substr(commaIndex);
                            while(commaIndex != std::string::npos)
                            {
                                commaIndex = tempTwo.find_first_of(',');
                                ++edgeCount;
                                tempTwo = tempTwo.substr(commaIndex+1);
                                if(edgeCount == 5)
                                {
                                    tempTwo.erase(0,1);
                                    airportCodeTemp = tempTwo.substr(0,3);
                                    if(airportCode[0] == '"')
                                       airportCode = "";
                                }
                                else if(edgeCount == 7)
                                {
                                    latitude2 = tempTwo.substr(0,tempTwo.find_first_of(','));
                                }
                                else if(edgeCount == 8)
                                {
                                    longitude2 = tempTwo.substr(0,tempTwo.find_first_of(','));
                                }
                            }
                            if(airportCodeTemp == destination)
                                break;
                        }
                        edgeLocation.clear();
                        edgeLocation.seekg(0,std::ios::beg);
                        QDomElement xml = document.createElement("Edge");


                        int tempThree;
                        int airlineCount = 0;
                        std::string actualAirlineName;
                        std::string airlineIDFile;
                        std::string airlineMore;
                        std::string cutTemp;
                        while(getline(airlineInfo,airlineIDFile))
                        {
                             tempThree = airlineIDFile.find_first_of(',');
                             cutTemp = airlineIDFile.substr(tempThree);
                             while(tempThree != std::string::npos)
                             {
                                tempThree = cutTemp.find_first_of(',');
                                cutTemp = cutTemp.substr(tempThree+1);
                                ++airlineCount;
                                if(airlineCount == 1)
                                {
                                    actualAirlineName = cutTemp.substr(1,cutTemp.find_first_of(',')-2);
                                }
                                else if(airlineCount == 3)
                                {
                                    airlineMore = cutTemp.substr(1,cutTemp.find_first_of(',')-2);
                                    break;
                                }
                             }

                             airlineCount = 0;
                             if(airlineMore == airline)
                             {
                                 airline = actualAirlineName;
                                 break;
                             }
                        }
                        airlineInfo.clear();
                        airlineInfo.seekg(0,std::ios::beg);
                        xml.setAttribute("Carrier",QString::fromStdString(airline));
                        xml.setAttribute("Destination",QString::fromStdString(destination));
                        distance = calculateDistance(atof(latitude.c_str()),atof(latitude2.c_str()),atof(longitude.c_str()),atof(longitude2.c_str()));
                        xml.setAttribute("Distance",QString::number(distance));
                        node.appendChild(xml);
                        break;
                    }
                }
                count = 0;
            }
        }
        ++index;
        if(index == 11)
        {
            index = 0;
            routes.clear();
            routes.seekg(0,std::ios::beg);
        }
    }
    input.close();
    routes.close();

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"Failed to open file for writing";
        return -1;
    }
    else
    {
        QTextStream stream(&file);
        stream<<document.toString();
        file.close();
        qDebug()<<"Finished";
    }

    return a.exec();
}

double DegToRad(const double& deg)
{
    return deg*3.14/180;
}

double calculateDistance(double lat1,double lat2, double long1,double long2)
{
   double earthRadius=6371;
    lat1=DegToRad(lat1);
    long1=DegToRad(long1);
    lat2=DegToRad(lat2);
    long2=DegToRad(long2);
    double diffLat = fabs(lat1-lat2), diffLon=fabs(long1 - long2);
    double distance=2*asin(sqrt(pow(sin(diffLat/2),2.0)+cos(lat1)*cos(lat2)*pow(sin(diffLon/2),2.0)))*earthRadius;
    return distance;
}


