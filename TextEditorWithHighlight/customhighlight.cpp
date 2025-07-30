#include "customhighlight.h"

CustomHighlight::CustomHighlight(QTextEdit *editor, QObject *parent)
    : QObject(parent), m_editor(editor)
{
    /*
        При любом изменении текста в эдиторе вызывается слот хайлайтера
    */
    connect(m_editor, &QTextEdit::textChanged, this, &CustomHighlight::highlighting);
}

void CustomHighlight::highlighting()
{
    /*
        Делаем подсчет количества слов в написанном тексте
    */
    QMap<QString, int> m_wordsCount;
    QString text = this->m_editor->toPlainText().toLower();

    /*
        Указываем регулярным выражением, что хотим обрабатывать
        русские, латинские символы и цифры
    */
    QStringList words = text.split(QRegularExpression(R"([^\p{L}\d]+)"), Qt::SkipEmptyParts);

    for (QString& word : words)
        m_wordsCount[word] ++;

    /*
        Отключение сигналов эдитора, что бы не было бесконечного цикла
        т.к изменение текста тоже является вызовом сигнала textChanged
    */
    m_editor->blockSignals(true);

    QTextDocument* doc = m_editor->document();
    QTextCursor cursor(doc);

    /*
        Создаем итератор для получения позиции слов,
        удовлетворяющих условиям регулярного выражения
    */
    QRegularExpression wordPattern("\\b[a-zA-Zа-яА-Я0-9]+\\b", QRegularExpression::UseUnicodePropertiesOption);
    QRegularExpressionMatchIterator matchIter = wordPattern.globalMatch(doc->toPlainText().toUtf8());

    while (matchIter.hasNext()) {
        /*
            Получаем слово удовлетворяющее паттерну, получаем его позицию и длину
        */
        QRegularExpressionMatch match = matchIter.next();
        int position = match.capturedStart();
        int length = match.capturedLength();

        qDebug() << length;

        /*
            Выделяем слово курсором
        */
        cursor.setPosition(position);
        cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, length);


        QTextCharFormat format; // Формат для изменения цвета слов

        QString selectedWord = cursor.selectedText().trimmed().toLower(); // Слово, которое мы выделили курсором

        /*
            Проверка выделенного слова на количество его повторений
            и определение ее цвета в зависимости от количества повторений
        */
        if (m_wordsCount[selectedWord] == 1) format.setForeground(Qt::green);
        else if (m_wordsCount[selectedWord] == 2) format.setForeground(Qt::black);
        else if (m_wordsCount[selectedWord] >= 3) format.setForeground(Qt::red);
        else format.setForeground(Qt::black);


        cursor.mergeCharFormat(format); // Изменяем формат (в данном случае только цвет)
    }

    m_editor->blockSignals(false); // Обратно включаем сигналы эдитора
}
