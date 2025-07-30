#include "help.h"

Help::Help(QStringList list)
{
    QString line;

    for(int i(0); i <list.size(); i++){
        line.push_back(list[i]);
        if(i+1 < list.size()){
            line.push_back(" ");
        }
    }

    if (line == "help battery"){
        qDebug() << "list";
        qDebug() << "search";
        qDebug() << "help";
    }
    else if (line == "help battery list"){
        qDebug() << "Вывод всех батарей";
    }
    else if (line == "help battery search"){
        qDebug() << "Поиск батарей по заданным параметрам:";
        qDebug() << "Параметры:";
        qDebug() << "-i,--id";
        qDebug() << "-o, --object_name";
    }
    else if (line == "help createDB"){
        qDebug() << "Инициализация базы данных из файла JSON в соответсвующие таблицы";
    }
    else if (line == "help weapon"){
        qDebug() << "list";
        qDebug() << "help";
    }
    else if (line == "help weapon list"){
        qDebug() << "Вывод списка всех орудий";
    }
    else if (line == "help ammunition"){
        qDebug() << "list";
        qDebug() << "help";
    }
    else if (line == "help ammunition list"){
        qDebug() << "Вывод списка всех боеприпасов";
    }
    else if (line == "help object"){
        qDebug() << "list";
        qDebug() << "help";
        qDebug() << "possibility";
        qDebug() << "delete";
        qDebug() << "add";
    }
    else if (line == "help object list"){
        qDebug() << "Вывод списка всех целей";
    }
    else if (line  == "help object possibility"){
        qDebug() << "Вывод всех батарей, которые могут поразить данную цель";
        qDebug() << "Параметры:";
        qDebug() << "-i,--d";
    }
    else if (line == "help object delete"){
        qDebug() << "Удаление цели по id";
        qDebug() << "Параметры:";
        qDebug() << "-i,--id";
    }
    else if (line == "help object add"){
        qDebug() << "Добавление цели";
        qDebug() << "Параметры:";
        qDebug() << "-o,--object_name";
        qDebug() << "-x,--coord_x";
        qDebug() << "-y,--coord_y";
        qDebug() << "-h,--height";
    }
    else if (line == "help"){
        qDebug() << "createDB";
        qDebug() << "battery";
        qDebug() << "weapon";
        qDebug() << "ammunition";
        qDebug() << "object";
    }
    else {
        qDebug() << "createDB";
        qDebug() << "battery";
        qDebug() << "weapon";
        qDebug() << "ammunition";
        qDebug() << "object";

    }

}
