#include "list.h"


List::List(const QString &line)
{
    if (line == "battery") batteryList();
    else if (line == "weapon") weaponList();
    else if (line == "ammunition") ammunitionList();
    else if (line == "object") objectList();
    else showHelp();

    return;
}

void List::showHelp()
{
    qDebug() << "createDB";
    qDebug() << "battery";
    qDebug() << "weapon";
    qDebug() << "ammunition";
    qDebug() << "object";
}

void List::batteryList()
{
    query.exec("SELECT *FROM battery");
    while (query.next()) {
        QString data(">Батарея №%1, %2, Используемое орудие:%3, Используемые боеприпасы:%4, "
                     "X:%5, Y:%6, Высота:%7");
        QString weaponName(getWeaponName(query.value("weapon_id").toInt()));
        QString ammunName(getAmmunName(query.value("ammunition_id").toInt()));
        QStringList info(getBatteryInfo(query.value("info_id").toInt()));

        qDebug() << data.arg(query.value(0).toString()).arg(query.value(1).toString())
                    .arg(weaponName).arg(ammunName).arg(info.value(0)).arg(info.value(1)).arg(info.value(2));
    }
}

void List::weaponList()
{
    query.exec("SELECT *FROM weapon");
    while (query.next()) {
        QString data(">Орудие №%1, %2, Максимальная дальность стрельбы:%3м.");
        qDebug() << data.arg(query.value(0).toString()).arg(query.value(1).toString())
                    .arg(query.value(2).toString());
    }
}

void List::ammunitionList()
{
    query.exec("SELECT *FROM ammunition");
    while (query.next()) {
        QString data(">Боеприпас №%1, %2, Количество:%3шт.");
        qDebug() << data.arg(query.value(0).toString()).arg(query.value(1).toString())
                    .arg(query.value(2).toString());
    }
}

void List::objectList()
{
    query.exec("SELECT *FROM object");
    if (query.size()) {
        while (query.next()) {
            QString data(">Цель №%1, %2, X:%3, Y:%4, Высота:%5");
            QStringList info(getObjectInfo(query.value("info_obj_id").toInt()));

            qDebug() << data.arg(query.value(0).toString()).arg(query.value(1).toString())
                        .arg(info[0]).arg(info[1]).arg(info[2]);
        }
    } else {
        qDebug() << "Цели отсутствуют";
    }
}

QString List::getWeaponName(const int &id)
{
    QSqlQuery quer;
    quer.exec("SELECT *FROM weapon");
    while (quer.next())
        if (quer.value(0).toInt() == id)
            return quer.value("name").toString();

    return "";
}

QString List::getAmmunName(const int &id)
{
    QSqlQuery quer;
    quer.exec("SELECT *FROM ammunition");
    while (quer.next())
        if (quer.value(0).toInt() == id)
            return quer.value(1).toString();

    return "";
}

QStringList List::getObjectInfo(const int &id)
{
    QSqlQuery quer;
    quer.exec("SELECT *FROM info_obj");
    while (quer.next()) {
        if (quer.value(0).toInt() == id)
            return QStringList() << quer.value(1).toString() << quer.value(2).toString()
                                 << quer.value(3).toString();
    }
    return QStringList();
}

QStringList List::getBatteryInfo(const int &id)
{
    QSqlQuery quer;
    quer.exec("SELECT *FROM info");
    while (quer.next())
        if (quer.value(0).toInt() == id)
            return QStringList() << quer.value(1).toString() << quer.value(2).toString()
                                    << quer.value(3).toString();

    return QStringList();
}
