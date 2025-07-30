#include "posibility.h"


Posibility::Posibility()
{
    QCommandLineOption id_Opt(
                {"i", "id"},
                "spec for id",
                "id"
                );
    parser.addOption(id_Opt);
    parser.parse(QCoreApplication::arguments());

    if (parser.isSet(id_Opt) && (parser.value(id_Opt).isEmpty() || parser.value(id_Opt).at(0)  == '-'))
        qDebug() << "Пустое значение парамтера 'i'";
    else if (parser.value(id_Opt).isEmpty())
        qDebug() << "Не хватает обязательного параметра";
    else if (!isCurId(parser.value(id_Opt).toInt())){
        qDebug() << "Цели с таким id не существует";
    }
    else process1(parser.value(id_Opt).toInt());
}

void Posibility::process1(const int &id)
{
    //ЗАПРОС НА ПОЛУЧЕНИЯ КООРДИНАТ ЦЕЛИ ПО ID
    coord infoObj(getCoordObj(id));

    QSqlQuery query;
    query.exec("SELECT *FROM battery");
    while (query.next()) {
        coord infoBat(getCoordBat(query.value("info_id").toInt()));
        infoBat.id =  query.value("id").toInt();
        infoBat.name = query.value("name").toString();
        const int range(getRange(query.value("weapon_id").toInt()));



        if (isPossibility(infoObj.x, infoObj.y, infoBat.x, infoBat.y, range)){
            qDebug() << infoBat.id << infoBat.name;
        }



    }

}

bool Posibility::isCurId(const int &id)
{
    QSqlQuery query;
    query.exec("SELECT *FROM object");
    while(query.next())
        if (query.value("id") == id)
            return true;

    return false;
}

bool Posibility::isPossibility(const int &x1, const int &y1, const int &x2, const int &y2, const int &range)
{
    return ((sqrt(pow((x2-x1),2)+pow((y2-y1),2))) <= range);
}


Posibility::coord Posibility::getCoordBat(const int &id)
{
    QSqlQuery query;
    query.exec("SELECT *FROM info");
    while (query.next())
        if (query.value("id") == id){
            coord cor;
            cor.x = query.value("coord_x").toInt();
            cor.y = query.value("coord_y").toInt();

            return cor;
        }


    return coord();
}

Posibility::coord Posibility::getCoordObj(const int &id)
{
    coord cor;
    QSqlQuery query;
    query.exec("SELECT *FROM info_obj");
    while (query.next())
        if (query.value("id") == id){
            cor.x = query.value("coord_x").toInt();
            cor.y = query.value("coord_y").toInt();
            cor.id = id;

            break;
        }


    query.exec("SELECT *FROM object");
    while(query.next()){
        if (query.value("id").toInt() == id){
            cor.name = query.value("name").toString();
            return cor;
        }
    }

    return cor;
}

int Posibility::getRange(const int &id)
{
    QSqlQuery query;
    query.exec("SELECT *FROM weapon");
    while (query.next())
        if(query.value("id") == id)
            return query.value("range").toInt();

    return 0;
}
