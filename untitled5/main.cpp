#include <QCoreApplication>
#include <QtCore>
#include <QDebug>
#include <QFile>
#include <QtXml>
#include <iostream>

void ListElements(QDomElement root, QString tagname, QString attribute)
{
    QDomNodeList items = root.elementsByTagName(tagname);

    for(int i = 0; i < items.count(); i++)
    {
        QDomNode itemnode = items.at(i);
        if(itemnode.isElement())
        {
            QDomElement itemele = itemnode.toElement();
            std::cout<<itemele.attribute(attribute).toStdString()<<std::endl;
        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QFile file("output.xml");
    QDomDocument document;

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
    QDomElement root = document.firstChildElement();
    QDomNodeList items = root.elementsByTagName("Vertex");
    qDebug()<<"Total item = "<<items.count();
    for(int i = 0; i < items.count(); i++)
    {
        QDomNode booknode = items.at(i);
        if(booknode.isElement());
        {
            QDomElement book = booknode.toElement();
            ListElements(book,"Edge","Distance");
            ListElements(book,"Edge","Carrier");
            ListElements(book,"Edge","Destination");
        }
    }



    return a.exec();
}
