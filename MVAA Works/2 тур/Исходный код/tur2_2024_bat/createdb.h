#ifndef CREATEDB_H
#define CREATEDB_H

#include <QSqlDatabase>
#include <QSqlQuery>

#include <QStringList>

#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include <QDebug>


class CreateDB
{
public:
    CreateDB(QSqlDatabase &db);

private:
    QSqlQuery query;
    //------------------------------------------------------------------------------------------------
    void createTables();
    void readFiles();
    //------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------
    void readWeapon(const QJsonArray &array);
    void readAmmunition(const QJsonArray &array);
    void readBattery(const QJsonArray &array);
    void readInfo(const QJsonArray &array);
    //------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------
    void addDataFromWeapon(const int &id, const QString &name, const int &range);
    void addDataFromAmmun(const int &id, const QString &name, const int &count);
    void addDataFromBatt(const int &id, const QString &name, const int &weap_id,
                         const int &ammun_id, const int &info_id);
    void addDataFromInfo(const int &id, const int &cor_x, const int &cor_y, const int &height);
    //------------------------------------------------------------------------------------------------
};

#endif // CREATEDB_H
