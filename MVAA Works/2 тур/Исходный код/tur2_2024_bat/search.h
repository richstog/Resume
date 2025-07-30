#ifndef SEARCH_H
#define SEARCH_H

#include <QCoreApplication>

#include <QCommandLineParser>
#include <QCommandLineOption>

#include <QSqlQuery>

#include <QDebug>


class Search
{
public:
    Search();

private:
    QCommandLineParser parser;
    QSqlQuery query;
};

#endif // SEARCH_H
