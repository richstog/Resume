#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>

#include "customhighlight.h"

#define WindowTitle "TextEditorWithHighlight"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void newFile(); // Создание нового файла
    void openFile(); // Открытие файла
    bool saveFile(); // Сохранение файла
    void exitProgram(); // Выход из программы (с сохранение изменений)

private:
    QTextEdit* m_textEditor; // Основной виджет проекта
    CustomHighlight* m_highlighter; // Объект класса реализующий подсветку

    QString m_filePath = ""; // Строка для хранения пути к открытому файлу

    /*
        Объекты реализации верхнего меню
    */
    QMenuBar* m_menuBar;
    QMenu* m_fileMenu;

    bool isChanged();
};
#endif // MAINWINDOW_H
