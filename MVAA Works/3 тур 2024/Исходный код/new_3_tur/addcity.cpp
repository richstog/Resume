#include "addcity.h"
#include "ui_addcity.h"


AddCity::AddCity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCity)
{
    ui->setupUi(this);

    connect(ui->lineEdit_2, &QLineEdit::textEdited, this, &AddCity::enabled_pushbotton);
    connect(ui->lineEdit_3, &QLineEdit::textEdited, this, &AddCity::enabled_pushbotton);
    connect(ui->lineEdit_4, &QLineEdit::textEdited, this, &AddCity::enabled_pushbotton);

    QRegularExpression t1("[0-9]|[1-9][0-9]|[1-4][0-9][0-9]|[5][0][0]");
    QValidator *val1 = new QRegularExpressionValidator(t1);

    ui->lineEdit_2->setValidator(val1);

    QRegularExpression t2("[0-9]|[1-9][0-9]|[1-4][0-9][0-9]|[5][0][0]");
    QValidator *val2 = new QRegularExpressionValidator(t2);

    ui->lineEdit_3->setValidator(val2);

    QRegularExpression t3("[0-9]|[1-9][0-9]|[1-9][0-9][0-9]|[1-9][0-9][0-9][0-9]|[1-9][0-9][0-9][0-9][0-9]|[1-9][0-9][0-9][0-9][0-9][0-9]|[1-9][0-9][0-9][0-9][0-9][0-9][0-9]|[5][0][0][0][0][0][0]");
    QValidator *val3 = new QRegularExpressionValidator(t3);

    ui->lineEdit_4->setValidator(val3);
}

AddCity::~AddCity()
{
    delete ui;
}

AddCity::data AddCity::value()
{
    data dat;
    dat.name = ui->lineEdit->text();
    dat.x = ui->lineEdit_2->text().toInt();
    dat.y = ui->lineEdit_3->text().toInt();
    dat.count = ui->lineEdit_4->text().toInt();

    return dat;
}

void AddCity::enabled_pushbotton()
{
    if (ui->lineEdit->text() != "" &&
            ui->lineEdit_2->text() != "" &&
            ui->lineEdit_3->text() != "" &&
            ui->lineEdit_4->text() != "") {
        ui->pushButton->setEnabled(true);
    } else
        ui->pushButton->setEnabled(false);
}

