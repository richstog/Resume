#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_textEditor = new QTextEdit(this);
    m_highlighter = new CustomHighlight(m_textEditor);

    /*
        Создание верхнего меню
    */
    m_menuBar = new QMenuBar(this);
    m_fileMenu = new QMenu("File");
    m_fileMenu->addAction("New File", this, &MainWindow::newFile);
    m_fileMenu->addAction("Open File", this, &MainWindow::openFile);
    m_fileMenu->addAction("Save File", this, &MainWindow::saveFile);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction("Exit", this, &MainWindow::exitProgram);
    m_menuBar->addMenu(m_fileMenu);

    /*
        Настройки главного окна
    */
    setMenuBar(m_menuBar);
    setCentralWidget(m_textEditor);
    setWindowTitle(WindowTitle);
    setMinimumSize(QSize(500, 400));
}

MainWindow::~MainWindow() {}

/*
    При создании нового файла, чистим информацию о предыдущем файле и эдитор
    Также не забываем и про выбор сохранения изменений
*/
void MainWindow::newFile()
{
    if (!isChanged())
    {
        m_textEditor->clear();
        m_filePath.clear();
        setWindowTitle(WindowTitle);
        return;
    }

    int res = QMessageBox::question(this, "Предупреждение", "Сохранить изменения?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    if (res == QMessageBox::Yes || res == QMessageBox::No)
    {
        if (res == QMessageBox::Yes)
            if(!saveFile()) return;
        m_textEditor->clear();
        m_filePath.clear();
        setWindowTitle(WindowTitle);
    }
}

void MainWindow::openFile()
{
    /*
        Вначале сохраняем файл (если хотим)
    */
    if (isChanged())
    {
        int res = QMessageBox::question(this, "Предупреждение", "Сохранить изменения?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if (res == QMessageBox::Yes || res == QMessageBox::No)
        {
            if (res == QMessageBox::Yes)
                if(!saveFile()) return;
        }
        else return;
    }

    /*
        Обновляем данные о файле и выводим содерживое в эдитор
    */
    m_filePath = QFileDialog::getOpenFileName(this, "Open file", "", "");
    QFile file(m_filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Error file open!" << file.errorString();
        return;
    }

    QTextStream in(&file);
    m_textEditor->setPlainText(in.readAll());
    setWindowTitle(QFileInfo(file.fileName()).fileName());

    file.close();
}

/*
    Если файл уже существует, то файл перезаписывается,
    а если файла не существовало, то создается файл
    и в него все записывается из эдитора
*/
bool MainWindow::saveFile()
{
    if (!isChanged()) // Если файл не был изменен, то сохранять нечего
        return true;

    if (m_filePath.isEmpty())
        m_filePath = QFileDialog::getSaveFileName(this, "Save file", "", "");

    if (m_filePath.isEmpty())
        return false;

    QFile file(m_filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qWarning() << "Error file open!" << file.errorString();
        return false;
    }

    QTextStream out(&file);
    out << m_textEditor->toPlainText();
    setWindowTitle(QFileInfo(file.fileName()).fileName());

    file.close();

    return true;
}

/*
    Выход из приложения с предложением о сохранении изменений
*/
void MainWindow::exitProgram()
{
    if (!isChanged())
    {
        close();
        return;
    }

    int res = QMessageBox::question(this, "Предупреждение", "Сохранить изменения?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    if (res == QMessageBox::Yes || res == QMessageBox::No)
    {
        if (res == QMessageBox::Yes)
            if(!saveFile()) return;
        close();
    }
}

/*
    Функция которая везде будет проверять изменялся ли файл от своего исходного состояния или нет.
    P.s. можно было бы сделать как слот на сигнал изменения текста, но т.к. подсветка тоже вызывает этот сигнал
    изменением цвета слов, то будет бесполезно таким способом проверять был ли изменен файл
*/
bool MainWindow::isChanged()
{
    if (m_textEditor->toPlainText().isEmpty() && m_filePath.isEmpty())
        return false;

    QFile file(m_filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return true;

    if (file.readAll() == m_textEditor->toPlainText())
        return false;
    else
        return true;
}
