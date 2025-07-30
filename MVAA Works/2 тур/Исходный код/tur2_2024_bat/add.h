#ifndef ADD_H
#define ADD_H

#include <QCoreApplication>

#include <QCommandLineParser>
#include <QCommandLineOption>

#include <QSqlQuery>

#include <QDebug>


class Add
{
public:
    Add();

private:
    QSqlQuery query;
    QCommandLineParser parser;
    QString errMessage;

    void checkEmptyVal();
    int getIdObj();
    bool isCurCoord(const int &cor_x, const int &cor_y);

    bool addData(const int &id, const QString &name, const int &cor_x, const int &cor_y,
                 const int &height);
};

#endif // ADD_H
