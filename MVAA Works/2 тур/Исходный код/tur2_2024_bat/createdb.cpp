#include "createdb.h"


CreateDB::CreateDB(QSqlDatabase &db)
{
    if (db.open() && db.tables().size() < 6) {
        createTables();
        readFiles();
    }

    qDebug() << "База данных успешно проинициализирована";
}

void CreateDB::createTables()
{
    query.exec("CREATE TABLE weapon ("
               "id INTEGER,"
               "name VARCHAR (20),"
               "range INTEGER"
               ");");
    query.exec("CREATE TABLE ammunition ("
               "id INTEGER,"
               "name VARCHAR (15),"
               "count INTEGER"
               ");");
    query.exec("CREATE TABLE info ("
               "id INTEGER,"
               "coord_x INTEGER,"
               "coord_y INTEGER,"
               "heigth INTEGER"
               ");");
    query.exec("CREATE TABLE battery ("
               "id INTEGER,"
               "name VARCHAR (15),"
               "weapon_id INTEGER,"
               "ammunition_id INTEGER,"
               "info_id INTEGER"
               ");");
    query.exec("CREATE TABLE object ("
               "id INTEGER,"
               "name VARCHAR (30),"
               "info_obj_id INTEGER"
               ");");
    query.exec("CREATE TABLE info_obj ("
               "id INTEGER,"
               "coord_x INTEGER,"
               "coord_y INTEGER,"
               "height INTEGER"
               ");");
}

void CreateDB::readFiles()
{
    QFile file("data_bat.JSON");
    if (file.open(QIODevice::ReadOnly)) {

        QString data(file.readAll());
        QJsonDocument document(QJsonDocument::fromJson(data.toUtf8()));
        QJsonObject obj(document.object());
        QJsonObject::iterator it = obj.begin();

        while (it != obj.end()) {
            if (it.key().toStdString() == "weapon") readWeapon(it.value().toArray());
            if (it.key().toStdString() == "ammunition") readAmmunition(it.value().toArray());
            if (it.key().toStdString() == "battery") readBattery(it.value().toArray());
            if (it.key().toStdString() == "info") readInfo(it.value().toArray());

            ++ it;
        }
    }
}

void CreateDB::readWeapon(const QJsonArray &array)
{
    for (int i(0); i < array.size(); i ++) {

        QJsonObject obj(array[i].toObject());
        addDataFromWeapon(obj.value("id").toInt(), obj.value("name").toString(),
                          obj.value("range").toInt());
    }
}

void CreateDB::readAmmunition(const QJsonArray &array)
{
    for (int i(0); i < array.size(); i ++) {

        QJsonObject obj(array[i].toObject());
        addDataFromAmmun(obj.value("id").toInt(), obj.value("name").toString(),
                         obj.value("count").toInt());
    }
}

void CreateDB::readBattery(const QJsonArray &array)
{
    for (int i(0); i < array.size(); i ++) {

        QJsonObject obj(array[i].toObject());
        addDataFromBatt(obj.value("id").toInt(), obj.value("name").toString(),
                        obj.value("weapon_id").toInt(), obj.value("ammunition_id").toInt(),
                        obj.value("info_id").toInt());

    }
}

void CreateDB::readInfo(const QJsonArray &array)
{
    for (int i(0); i < array.size(); i ++) {

        QJsonObject obj(array[i].toObject());
        addDataFromInfo(obj.value("id").toInt(), obj.value("coord_x").toInt(),
                        obj.value("coord_y").toInt(), obj.value("height").toInt());
    }
}

void CreateDB::addDataFromWeapon(const int &id, const QString &name, const int &range)
{
    QString execStr("INSERT INTO weapon (id, name, range) VALUES (%1, '%2', %3)");
    query.prepare(execStr.arg(id).arg(name).arg(range));
    query.exec();
}

void CreateDB::addDataFromAmmun(const int &id, const QString &name, const int &count)
{
    QString execStr("INSERT INTO ammunition (id, name, count) VALUES (%1, '%2', %3)");
    query.prepare(execStr.arg(id).arg(name).arg(count));
    query.exec();
}

void CreateDB::addDataFromBatt(const int &id, const QString &name, const int &weap_id,
                               const int &ammun_id, const int &info_id)
{
    QString execStr("INSERT INTO battery (id, name, weapon_id, ammunition_id, info_id) "
                    "VALUES (%1, '%2', %3, %4, %5)");
    query.prepare(execStr.arg(id).arg(name).arg(weap_id).arg(ammun_id).arg(info_id));
    query.exec();
}

void CreateDB::addDataFromInfo(const int &id, const int &cor_x, const int &cor_y, const int &height)
{
    QString execStr("INSERT INTO info (id, coord_x, coord_y, heigth) VALUES (%1, %2, %3, %4)");
    query.prepare(execStr.arg(id).arg(cor_x).arg(cor_y).arg(height));
    query.exec();
}
