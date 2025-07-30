#include "deleter.h"


Deleter::Deleter(const QStringList &list)
{
    //--------------------------------------------------------------------------------------------------------
    parser.setApplicationDescription("parser");

    QCommandLineOption id_Opt(
                {"i", "id"},
                "spec for id",
                "id"
                );
    parser.addOption(id_Opt);
    parser.parse(QCoreApplication::arguments());
    //--------------------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------------
    if (parser.isSet(id_Opt) && (parser.value(id_Opt).isEmpty() || parser.value(id_Opt).at(0) == '-'))
        qDebug() << "Пустое значение параметра 'i'.Удаление невозможно";
    else if (!parser.isSet(id_Opt))
        qDebug() << "Не хватает обязательного параметра. Удаление невозможно";
    else {
        const int id(parser.value(id_Opt).toInt());

        if (deleteObj(id))
            if (deleteInfo_Obj(id))
                qDebug() << "Цель успешно удалена";
    }
    //--------------------------------------------------------------------------------------------------------
}

bool Deleter::deleteObj(const int &id)
{
    QString execStr("DELETE FROM object WHERE id = %1");
    query.prepare(execStr.arg(id));

    return query.exec();
}

bool Deleter::deleteInfo_Obj(const int &id)
{
    QString execStr("DELETE FROM info_obj WHERE id = %1");
    query.prepare(execStr.arg(id));

    return query.exec();
}
