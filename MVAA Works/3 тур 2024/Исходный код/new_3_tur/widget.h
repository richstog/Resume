#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QPushButton>
#include <QComboBox>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QFileDialog>

#include <string>

#include <canvas.h>


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Canvas *canvas;
    QVBoxLayout *layout;

    void addButtons();

private slots:
    void readFile();
    void process();
};
#endif // WIDGET_H
