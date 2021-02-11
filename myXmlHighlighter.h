/*************************************************
 *
 *  Наименование: Подсветка XML-кода
 *  Версия: 1.2
 *  Дата написания: 25.01.2020
 *  Используемый язык: Qt/C++
 *  Написал: Семенов Д.С.
 *
 *  Описание цели класса:
 *  Класс подзволяет выделять теги XML (кастомных тегов) в объектах текста.
 *  Например, подсветка работает с QPlainText или других объектах,
 *  которые могут возвратить содержимое в виде типа QTextDocument.
 *
 *  Поддерживаемые теги:
 *  1.Task      ;
 *  2.Delete    ;
 *  3.Start     ;
 *  4.OpenScen  ;
 *  5.Scen      ;
 *  6.Copy      ;
 *  7.File      ;
 *  8.Var       .
 *
 *  Описание структуры класса:
 *  Большая часть кода взята из https://evileg.com/ru/post/218/
 *
 *  Платформа: OC Windows
 *
 **************************************************************
 * Программа выполнена в рамках проекта редактора сценариев
 * экспертной системы
 **************************************************************
 */

#ifndef MYXMLHIGHLIGHTER_H
#define MYXMLHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextDocument>

class myXMLHighlighter : QSyntaxHighlighter
{
    Q_OBJECT
public:
    myXMLHighlighter(QTextDocument *parent = nullptr);

    void setHighlightedString(QString &str, const int & numberBlock );

protected:
    void highlightBlock(const QString &text) override;

private:
    // Состояние подсветки, в которой находится текстовый блок на момент его закрытия
    enum States {
        None,       // Без подсветки
        Tag,        // Подсветка внутри тега
        Comment,    // Внутри комментария
        Quote       // Внутри кавычек, которые внутри тега
    };

    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };

    QVector<HighlightingRule> startTagRules;    // Правила форматирования для открывающих тегов
    QVector<HighlightingRule> endTagRules;      // Правила форматирования для закрывающих тегов

    QRegExp openTag;                            // Символ открытия тега   - "<"
    QRegExp closeTag;                           // Символ закрытия тег    - ">"
    QTextCharFormat edgeTagFormat;              // Форматирование символов openTag и closeTag
    QTextCharFormat insideTagFormat;            // Форматирование текста внутри тега

    QRegExp commentStartExpression;             // Регулярка начала комментария
    QRegExp commentEndExpression;               // Регулярка закрытия комментария
    QTextCharFormat multiLineCommentFormat;     // Форматирование текста внутри комментария

    QRegExp quotes;                             // Регулярное выражение для текста в кавычках внутри тега
    QTextCharFormat quotationFormat;            // Форматирование текста в кавычках внутри тега
    QTextCharFormat tagsFormat;                 // Форматирование самих тегов

private:
    QString m_highlightedString;
    QString m_highlightedStringClose;

    bool flagSetStr = false;
    bool flagSecondBypass = false;

    int countCloseTag = 0;
    int countOpenTag = 0;
    int numberBlock = 0;
    int i = 0;
    int itOfCurrent = 0;

    QStringList keywordPatterns2,keywordPatternsClose;
};

#endif // MYXMLHIGHLIGHTER_H
