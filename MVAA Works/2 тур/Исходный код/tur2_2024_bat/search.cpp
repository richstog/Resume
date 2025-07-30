#include "search.h"

Search::Search()
{
    parser.setApplicationDescription("parser");

    QCommandLineOption id_Opt(
                {"i", "id"},
                "spec for id",
                "id"
                );
    QCommandLineOption name_Opt(
                {"b", "battery_name"},
                "spec for name",
                "name"
                );

    parser.addOptions(QList <QCommandLineOption>() << id_Opt << name_Opt);
    parser.parse(QCoreApplication::arguments());

    if (!parser.isSet(id_Opt) && !parser.isSet(name_Opt))
        qDebug() << "Ни один параметр не задан";
    else if (parser.isSet(id_Opt) && (parser.value(id_Opt).isEmpty() || parser.value(id_Opt).at(0) == '-'))
        qDebug() << "Пустое занчение параметра 'i' ";
    else if (parser.isSet(name_Opt) && (parser.value(name_Opt).isEmpty() || parser.value(name_Opt).at(0) == '-'))
        qDebug() << "Пустое занчение параметра 'b' ";
    else {
        QString execStr("SELECT *FROM battery WHERE ");

        if (!parser.value(id_Opt).isEmpty()) {
            execStr.push_back(QString("id = %1").arg(parser.value(id_Opt)));
            if (!parser.value(name_Opt).isEmpty())
                execStr.push_back(QString(" AND name = '%1'").arg(parser.value(name_Opt)));
        } else execStr.push_back(QString("name = '%1'").arg(parser.value(name_Opt)));

        query.exec(execStr);
        if (!query.size()) qDebug() << "По запросу ничего не найдено";
        else {
            while (query.next()) {
                qDebug() << "|-->Батарея №" + query.value(0).toString() + ", "
                            + query.value(1).toString();
            }
        }
    }
}
