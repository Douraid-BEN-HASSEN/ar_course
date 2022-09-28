
#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <qlist.h>

#include <QObject>
#include <QMap>
#include <QDebug>

#include <checkpoint.h>

#include <QList>

#include <iostream>
#include <vector>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>


class Map
{
public:
    Map();

    void setHeight(int height);
    int getHeight();
    void setWigth(int wigth);
    int getWigth();
    void deserialize(const QJsonObject &jsonObject) ;
    QJsonObject toJson() ;

    QString serialize();


public:

    float m_height;
    float m_wigth;

};

#endif // MAP_H

