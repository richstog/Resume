#ifndef LIST_H
#define LIST_H

#include <QSqlQuery>

#include <QDebug>


class List
{

public:
    List(const QString &line);

private:
    QSqlQuery query;

    void showHelp();
    void batteryList();
    void weaponList();
    void ammunitionList();
    void objectList();

    QString getWeaponName(const int &id);
    QString getAmmunName(const int &id);
    QStringList getObjectInfo(const int &id);
    QStringList getBatteryInfo(const int &id);

};

#endif // LIST_H
