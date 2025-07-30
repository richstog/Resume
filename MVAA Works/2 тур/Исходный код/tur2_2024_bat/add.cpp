#include "add.h"

Add::Add()
{
    //--------------------------------------------------------------------------------------------------------
    parser.setApplicationDescription("parser");

    QCommandLineOption name_Opt(
                {"o", "object_name"},
                "spec for obj_name",
                "object_name"
                );
    QCommandLineOption cor_X_Opt(
                {"x", "coord_x"},
                "spec for cor_x",
                "coord_x"
                );
    QCommandLineOption cor_Y_Opt(
                {"y", "coord_y"},
                "spec for cor_y",
                "coord_y"
                );
    QCommandLineOption height_Opt(
                {"h", "height"},
                "spec for height",
                "height"
                );

    parser.addOptions(QList <QCommandLineOption>() << name_Opt << cor_X_Opt <<
                      cor_Y_Opt << height_Opt);
    parser.parse(QCoreApplication::arguments());
    //--------------------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------------
    if (parser.isSet(name_Opt) && (parser.value(name_Opt).isEmpty() || parser.value(name_Opt).at(0) == '-'))
        errMessage = "Пустое значение параметра 'o'";
    else if (parser.isSet(cor_X_Opt) && (parser.value(cor_X_Opt).isEmpty() || parser.value(cor_X_Opt).at(0) == '-'))
        errMessage = "Пустое значение параметра 'x'";
    else if (parser.isSet(cor_Y_Opt) && (parser.value(cor_Y_Opt).isEmpty() || parser.value(cor_Y_Opt).at(0) == '-'))
        errMessage = "Пустое значение параметра 'y'";
    else if (parser.isSet(height_Opt) && (parser.value(height_Opt).isEmpty() || parser.value(height_Opt).at(0) == '-'))
        errMessage = "Пустое значение параметра 'h'";
    //--------------------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------------
    if (!errMessage.isEmpty())
        qDebug() << errMessage;
    else if (parser.value(name_Opt).isEmpty() || parser.value(cor_X_Opt).isEmpty() ||
             parser.value(cor_Y_Opt).isEmpty() || parser.value(height_Opt).isEmpty())
        qDebug() << "Не хватает обязательных параметров";
    else {
        const int cor_x(parser.value(cor_X_Opt).toInt());
        const int cor_y(parser.value(cor_Y_Opt).toInt());

        if (!isCurCoord(cor_x, cor_y)) qDebug() << "Цель вне рабочей области.Добваление невозможно";
        else {
            int obj_Id(getIdObj());

            if (addData(obj_Id, parser.value(name_Opt), parser.value(cor_X_Opt).toInt(),
                        parser.value(cor_Y_Opt).toInt(), parser.value(height_Opt).toInt()))
                qDebug() << "Цель успешно добавлена.";
        }
    }
    //--------------------------------------------------------------------------------------------------------
}

int Add::getIdObj()
{
    int id(0);
    query.exec("SELECT *FROM object");
    while (query.next())
        id = qMax(id, query.value(0).toInt());

    return id + 1;
}

bool Add::isCurCoord(const int &cor_x, const int &cor_y)
{
    return ((cor_x >= 20000 && cor_x <= 40000) && (cor_y >= 15000 && cor_y <= 30000));
}

bool Add::addData(const int &id, const QString &name, const int &cor_x, const int &cor_y, const int &height)
{
    QString execStr("INSERT INTO object VALUES (%1, '%2', %3)");
    query.prepare(execStr.arg(id).arg(name).arg(id));
    if (query.exec()) {

        execStr = "INSERT INTO info_obj VALUES (%1, %2, %3, %4)";
        query.prepare(execStr.arg(id).arg(cor_x).arg(cor_y).arg(height));
        return query.exec();
    }
}
