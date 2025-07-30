#ifndef POSIBILITY_H
#define POSIBILITY_H

#include <QCoreApplication>

#include <QSqlQuery>

#include <QCommandLineParser>
#include <QCommandLineOption>
#include <math.h>

#include <QDebug>


class Posibility
{
public:
    Posibility();

private:
    QSqlQuery query;
    QCommandLineParser parser;
    struct coord {
        int id;
        QString name;
        int x;
        int y;
    };

    void process1(const int &id);

    coord getCoordBat(const int &id);
    coord getCoordObj(const int &id);

    int getRange(const int &id);
    int getInfoObjId(const int &id);

    bool isCurId(const int &id);
    bool isPossibility(const int &x1, const int &y1, const int &x2, const int &y2, const int &range);

};

#endif // POSIBILITY_H
