#ifndef CUSTOMHIGHLIGHT_H
#define CUSTOMHIGHLIGHT_H

#include <QObject>
#include <QWidget>
#include <QTextEdit>
#include <QMap>
#include <QRegularExpression>

class CustomHighlight : public QObject
{
    Q_OBJECT
public:
    explicit CustomHighlight(QTextEdit *editor, QObject* parent = nullptr);

public slots:
    void highlighting(); // Слот, описывающий весь функционал класс (подсветка слов)

private:

    QTextEdit* m_editor; // Указатель на эдитор для взаимодействия
};

#endif // CUSTOMHIGHLIGHT_H
