#include "addroads.h"
#include "ui_addroads.h"


AddRoads::AddRoads(const QStringList &list, QWidget *parent):
    QDialog(parent),
    ui(new Ui::AddRoads)
{
   ui->setupUi(this);

   foreach (QString line, list) {
       ui->comboBox->addItem(line);
       ui->comboBox_2->addItem(line);
   }
}

AddRoads::~AddRoads()
{
    delete ui;
}

AddRoads::data AddRoads::value()
{
    data dat;
    dat.x = ui->comboBox->currentIndex();
    dat.y = ui->comboBox_2->currentIndex();

    return dat;
}
