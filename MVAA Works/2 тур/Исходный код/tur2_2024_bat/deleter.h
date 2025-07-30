#ifndef DELETER_H
#define DELETER_H

#include <QSqlQuery>

#include <QCommandLineParser>
#include <QCommandLineOption>

#include <QDebug>


class Deleter
{
public:
    Deleter(const QStringList &list);

private:
    QCommandLineParser parser;
    QSqlQuery query;

    bool deleteObj(const int &id);
    bool deleteInfo_Obj(const int &id);
};

#endif // DELETER_H
