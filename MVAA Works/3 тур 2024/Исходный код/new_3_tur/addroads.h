#ifndef ADDROADS_H
#define ADDROADS_H

#include <QDialog>

#include <QDebug>


namespace Ui {
class AddRoads;
}

class AddRoads : public QDialog
{
    Q_OBJECT

public:
    explicit AddRoads(const QStringList &list, QWidget *parent = nullptr);

    ~AddRoads();

    struct data{
        int x;
        int y;
    };
    data value();

private:
    Ui::AddRoads *ui;
};

#endif // ADDROADS_H
