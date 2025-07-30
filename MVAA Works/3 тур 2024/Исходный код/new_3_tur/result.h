#ifndef RESULT_H
#define RESULT_H

#include <QDialog>

#include <QDebug>


namespace Ui {
class Result;
}

class Result : public QDialog
{
    Q_OBJECT

public:
    explicit Result(const QStringList &list, const int &townsSize, QWidget *parent = nullptr);
    ~Result();

    struct resultate {
        int a;
        int b;
    };

    resultate result();

private:
    Ui::Result *ui;
};

#endif // RESULT_H
