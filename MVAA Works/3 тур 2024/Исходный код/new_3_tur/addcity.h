#ifndef ADDCITY_H
#define ADDCITY_H

#include <QDialog>

#include <QRegularExpression>
#include <QRegularExpressionValidator>

namespace Ui {
class AddCity;
}

class AddCity : public QDialog
{
    Q_OBJECT

public:
    explicit AddCity(QWidget *parent = nullptr);
    ~AddCity();

    struct data {
        QString name;
        int x;
        int y;
        int count;
    };

    data value();

private slots:
    void enabled_pushbotton();

private:
    Ui::AddCity *ui;


};

#endif // ADDCITY_H
