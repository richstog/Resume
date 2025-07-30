#include <QCoreApplication>

#include <QSqlDatabase>

#include <QDebug>

#include <add.h>
#include <list.h>
#include <search.h>
#include <deleter.h>
#include <createdb.h>
#include <posibility.h>
#include <help.h>

QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

void connectDb()
{
    db.setHostName("astra");
    db.setDatabaseName("millitary_operations");
    db.setUserName("serg");
    db.setPassword("serg");

    db.open();
}

using namespace::std;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    connectDb();

    QStringList list(app.arguments());
    list.removeAt(0);

    if (list.size() == 1 && list[0] == "createDB") {                                //createDB
        CreateDB createDB(db);
        return 0;
    } else if (list.size() == 2 && list[1] == "list") {                             //List
        List lst(list[0]);
        return 0;
    } else if (list.size() >= 4 && list[0] == "battery" && list[1] == "search") {   //Search
        Search search;
        return 0;
    } else if (list.size() >= 2 && list[0] == "object" && list[1] == "add") {       //Add
        Add add;
        return 0;
    } else if (list.size() == 4 && list[0] == "object" && list[1] == "delete"){     //Delete
        Deleter deleter(list);
        return 0;
    } else if (list.size() >= 2 && list[0] == "object" && list[1] == "posibility"){ //Posibility
        Posibility posibility;
        return 0;
    } else {
        Help help(list);
    }

    return 0;
}
