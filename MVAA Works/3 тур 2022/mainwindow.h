#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChart>
#include <QEvent>
#include <QKeyEvent>
#include <QObject>
#include <QRegularExpression>
#include <QValidator>
#include <QVector>
#include <QFileDialog>

#include "solution.h"
#include "displaymap.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void Resize();
    void keyPressEvent(QKeyEvent *event);

    ~MainWindow();

private slots:

    bool no_rep(double,double);

    void nopush();

    void pushButton_1_active();

    void pushButton_2_active();

    void pushButton_3_active();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

public slots:

    void deletepoint(QString, QPointF);

private:
    Ui::MainWindow *ui;

    Displaymap map;
    QGraphicsScene *scene;

    void read(QString path, bool b);
    void on_push();
    bool no_repeat(double x, double y);
    void doc_vozm();
    void doc_opt();
};
#endif // MAINWINDOW_H
