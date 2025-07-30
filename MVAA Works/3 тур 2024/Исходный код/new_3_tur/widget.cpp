#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //--------------------------------------------------------------------------------------
    setWindowTitle("Города");

    setStyleSheet("background-color: Indigo; font-size: 20px; color: white; font-weight: 800;"
                  "font-family: Arial;");

    resize(1400, 900);
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    layout = new QVBoxLayout;
    setLayout(layout);

    canvas = new Canvas;
    layout->addWidget(canvas);

    addButtons();
    //--------------------------------------------------------------------------------------
}

Widget::~Widget()
{
}


void Widget::addButtons()
{
    QHBoxLayout *btnLayot = new QHBoxLayout;
    layout->addLayout(btnLayot);

    QPushButton *impBtn = new QPushButton("Импорт");
    btnLayot->addWidget(impBtn);
    connect(impBtn, &QPushButton::clicked, this, &Widget::readFile);

    QPushButton *expBtn = new QPushButton("Экспорт");
    btnLayot->addWidget(expBtn);
    connect(expBtn, &QPushButton::clicked, this, [=](){
        canvas->exportData();
    });

    QPushButton *clrBtn = new QPushButton("Очистить");
    btnLayot->addWidget(clrBtn);
    connect(clrBtn, &QPushButton::clicked, this, [=](){
       canvas->clear();
    });

    QPushButton *prcsBtn = new QPushButton("Расчитать");
    btnLayot->addWidget(prcsBtn);
    prcsBtn->setStyleSheet("background-color: green");
    connect(prcsBtn, &QPushButton::clicked, this, &Widget::process);
}

void Widget::readFile()
{
    QString filePath(QFileDialog::getOpenFileName(this,
                                                  tr("Open Image"), QDir::currentPath(), tr("Image Files (*.txt)")));
    qDebug() << filePath;

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        int countStr(file.readLine().toInt());

        while (!file.atEnd()) {
             if (countStr <= 0) break;

             QString name(file.readLine());
             name.remove(name.length() - 1, 1);
             int x(file.readLine().toInt());
             int y(file.readLine().toInt());
             int count(file.readLine().toInt());
             canvas->addPointRoad(name, x, y, count);

            countStr --;
        }
        file.readLine();

        QVector <QString> vec;
        while (!file.atEnd()) {
           vec.push_back(file.readLine());
        }

        QVector <QVector <int>> matric;
        for (int i(0); i < vec.size(); i ++) {

            QVector <int> line;
            std::string strLine(vec[i].toStdString());
            strLine.erase(strLine.end() - 1, strLine.end());
            for (int j(0); j < strLine.size(); j ++) {

                line.push_back(strLine[j] - 48);
            }

            matric.push_back(line);
        }

        canvas->saveMatrics(matric);
    }
}

void Widget::process()
{
    canvas->result();
}

