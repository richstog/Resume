#include "result.h"
#include "ui_result.h"


Result::Result(const QStringList &list, const int &townsSize, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Result)
{
    ui->setupUi(this);

    setWindowTitle("Расчет кратчайшего пути");

    foreach (const QString line, list) {
        ui->comboBox->addItem(line);
        ui->comboBox_2->addItem(line);
    }

    ui->pushButton_2->setEnabled(!(townsSize < 2));
}

Result::~Result()
{
    delete ui;
}

Result::resultate Result::result()
{
    resultate res;
    res.a = ui->comboBox->currentIndex();
    res.b = ui->comboBox_2->currentIndex();

    return res;
}

