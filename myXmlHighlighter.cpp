#include "myXmlHighlighter.h"
#include "qdebug.h"

myXMLHighlighter::myXMLHighlighter(QTextDocument *parent):
    QSyntaxHighlighter(parent)
{
    //Определение правил подсветки тегов (начала и конца)
    HighlightingRule rule;

    edgeTagFormat.setForeground(QBrush(QColor("#0099CC")));
    insideTagFormat.setForeground(QBrush(QColor("#9966FF")));
    insideTagFormat.setFontWeight(QFont::Bold);
    openTag = QRegExp("<");
    closeTag = QRegExp(">");

    tagsFormat.setForeground(QBrush(QColor("#0099CC")));
    tagsFormat.setFontWeight(QFont::Bold);

    //Начало всех существующих тегов
    QStringList keywordPatterns;
    keywordPatterns << "<\\bTask\\b"     << "<\\bScen\\b"
                    << "<\\bDelete\\b"   << "<\\bCopy\\b"
                    << "<\\bStart\\b"    << "<\\bFile\\b"
                    << "<\\bOpenScen\\b" << "<\\bVar\\b";

    for (const QString &pattern : keywordPatterns)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = tagsFormat;
        startTagRules.append(rule);
    }

    //Конец всех существующих тегов
    QStringList keywordPatterns_end;
    keywordPatterns_end << "</\\bTask\\b"     << "</\\bScen\\b"
                        << "</\\bDelete\\b"   << "</\\bCopy\\b"
                        << "</\\bStart\\b"    << "</\\bFile\\b"
                        << "</\\bOpenScen\\b" << "</\\bVar\\b";

    for (const QString &pattern : keywordPatterns_end)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = tagsFormat;
        endTagRules.append(rule);
    }

    multiLineCommentFormat.setForeground(Qt::darkGray);
    commentStartExpression = QRegExp("<!--");
    commentEndExpression = QRegExp("-->");

    quotationFormat.setForeground(QBrush(QColor(0,204,51)));
    quotes = QRegExp("\"");

    keywordPatterns2 << "<Task"     << "<Scen"
                     << "<Delete"   << "<Copy"
                     << "<Start"    << "<File"
                     << "<OpenScen>" << "<Var";

    keywordPatternsClose << "</Task>"     << "</Scen>"
                         << "</Delete>"   << "</Copy>"
                         << "</Start>"    << "</File>"
                         << "</OpenScen>" << "</Var>";
}

void myXMLHighlighter::highlightBlock(const QString &text)
{
    setCurrentBlockState(myXMLHighlighter::None);

    // TAG
    int startIndex = 0;

    // Если не находимся внутри тега
    if (previousBlockState() != myXMLHighlighter::Tag && previousBlockState() != myXMLHighlighter::Quote)
    {
        //Тогда пытаемся найти начало следующего тега
        startIndex = openTag.indexIn(text);
    }

    // Забираем состояние предыдущего текстового блока
    int subPreviousTag = previousBlockState();
    while (startIndex >= 0)
    {
        // ищем символ конца тега
        int endIndex = closeTag.indexIn(text, startIndex);

        int tagLength;
        // если конец тега не найден, то устанавливаем состояние блока
        if (endIndex == -1)
        {
            setCurrentBlockState(myXMLHighlighter::Tag);
            tagLength = text.length() - startIndex;
        }
        else
        {
            tagLength = endIndex - startIndex + closeTag.matchedLength();
        }

        // Устанавливаем форматирования для тега
        if (subPreviousTag != myXMLHighlighter::Tag)
        {
            // с начала тега и до конца, если предыдущее состояние не равнялось Tag
            setFormat(startIndex, 1, edgeTagFormat);
            setFormat(startIndex + 1, tagLength - 1, insideTagFormat);
        }
        else
        {
            // Если же находимся уже внутри тега с самого начала блока
            // и до конца тега
            setFormat(startIndex, tagLength, insideTagFormat);
            subPreviousTag = myXMLHighlighter::None;
        }
        // Форматируем символ конца тега
        setFormat(endIndex, 1, edgeTagFormat);

        /// QUOTES ///////////////////////////////////////
        int startQuoteIndex = 0;
        // Если не находимся в кавычках с предыдущего блока
        if (previousBlockState() != myXMLHighlighter::Quote)
        {
            // То пытаемся найти начало кавычек
            startQuoteIndex = quotes.indexIn(text, startIndex);
        }

        // Подсвечиваем все кавычки внутри тега
        while (startQuoteIndex >= 0 && ((startQuoteIndex < endIndex) || (endIndex == -1)))
        {
            int endQuoteIndex = quotes.indexIn(text, startQuoteIndex + 1);
            int quoteLength;
            if (endQuoteIndex == -1)
            {
                // Если закрывающая кавычка не найдена, то устанавливаем состояние Quote для блока
                setCurrentBlockState(myXMLHighlighter::Quote);
                quoteLength = text.length() - startQuoteIndex;
            }
            else
            {
                quoteLength = endQuoteIndex - startQuoteIndex + quotes.matchedLength();
            }

            if ((endIndex > endQuoteIndex) || endIndex == -1)
            {
                setFormat(startQuoteIndex, quoteLength, quotationFormat);
                startQuoteIndex = quotes.indexIn(text, startQuoteIndex + quoteLength);
            }
            else
            {
                break;
            }
        }
        //////////////////////////////////////////////////
        // Снова ищем начало тега
        startIndex = openTag.indexIn(text, startIndex + tagLength);
    }

    // EDGES OF TAGS
    // Обработка цвета саимх тегов, то есть подсветка слов div, p, strong и т.д.
    for (const HighlightingRule &rule : startTagRules)
    {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0)
        {
            int length = expression.matchedLength();
            setFormat(index + 1, length - 1, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }

    for (const HighlightingRule &rule : endTagRules)
    {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index + 1, 1, edgeTagFormat);
            setFormat(index + 2, length - 2, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }

    // COMMENT
    int startCommentIndex = 0;
    // Если предыдущее состояние тега не является комментарием
    if (previousBlockState() != myXMLHighlighter::Comment)
    {
        // то пытаемся найти начало комментария
        startCommentIndex = commentStartExpression.indexIn(text);
    }

    // Если комментарий найден
    while (startCommentIndex >= 0)
    {
        // Ищем конец комментария
        int endCommentIndex = commentEndExpression.indexIn(text, startCommentIndex);
        int commentLength;

        // Если конец не найден
        if (endCommentIndex == -1)
        {
            // То устанавливаем состояние Comment
            // Принцип аналогичен, что и для обычных тегов
            setCurrentBlockState(myXMLHighlighter::Comment);
            commentLength = text.length() - startCommentIndex;
        }
        else
        {
            commentLength = endCommentIndex - startCommentIndex
                            + commentEndExpression.matchedLength();
        }

        setFormat(startCommentIndex, commentLength, multiLineCommentFormat);
        startCommentIndex = commentStartExpression.indexIn(text, startCommentIndex + commentLength);
    }

    //----/////////////////////////////////////////////////////
    QTextCharFormat fmt;

    QColor color2("#f5f6fa");
    color2.setAlphaF(0.4);

    fmt.setBackground(color2);

    const int LEN = m_highlightedString.length();

    i++;

    if(keywordPatterns2.contains(m_highlightedString))
    {
        if(i == this->numberBlock)
        {
              setFormat( text.indexOf( m_highlightedString ), LEN, fmt ); // <Scen
              setFormat( text.indexOf( ">",  text.indexOf( m_highlightedString ) + LEN), 1, fmt ); // >
        }
        else if(i > this->numberBlock)
        {
            if(text.contains(m_highlightedString))
               countCloseTag += 1;
        }

        if((text.indexOf( m_highlightedStringClose ) >=0 )&&flagSetStr)
        {
            if(countCloseTag > 0)
            {
                countCloseTag-=1;
            }
            else
            {
               setFormat( text.indexOf( m_highlightedStringClose ),
                                       m_highlightedStringClose.length(), fmt ); // </Scen
               setFormat( text.indexOf( ">",  text.indexOf( m_highlightedStringClose ) ), 1, fmt );// >

               flagSetStr = false;
            }

        }

    }
    else if(keywordPatternsClose.contains(m_highlightedString))
    {
        if( i == this->numberBlock )
              setFormat( text.indexOf( m_highlightedString ), LEN, fmt ); // </Scen>

        if(i <= this->numberBlock && !flagSecondBypass)
        {
            if(text.contains(m_highlightedStringClose))
                countOpenTag++;
            else if(i != this->numberBlock && text.contains(m_highlightedString))
                countCloseTag++;
        }

        if((flagSecondBypass && text.indexOf( m_highlightedStringClose ) >=0 ))
        {
            itOfCurrent ++;

            if( itOfCurrent == (countOpenTag-countCloseTag) )
            {
               setFormat( text.indexOf( m_highlightedStringClose ),
                                       m_highlightedStringClose.length(), fmt ); // <Scen
               setFormat( text.indexOf( ">",  text.indexOf( m_highlightedStringClose ) + LEN), 1, fmt ); // >

               flagSecondBypass = false;
            }
        }
    }

}

void myXMLHighlighter::setHighlightedString( QString& str , const int &numberBlock)
{
    i = 0;
    countCloseTag = 0;
    countOpenTag = 0;
    itOfCurrent = 0;

    flagSetStr = true;
    flagSecondBypass = false;
    this->numberBlock = numberBlock+1;

    str.remove("\t");
    str.remove(0,str.indexOf("</"));

    if(keywordPatterns2.contains(str))
    {
        m_highlightedString = str;
        m_highlightedStringClose = str;
        m_highlightedStringClose.insert(1,"/");

        rehighlight();
    }
    else if(keywordPatternsClose.contains(str))
    {
        m_highlightedString = str;
        m_highlightedStringClose = str;
        m_highlightedStringClose.remove(1,1);
        m_highlightedStringClose.remove(m_highlightedStringClose.length()-1,1);

        rehighlight();

        i=0;
        flagSecondBypass = true;
        itOfCurrent =0;

        rehighlight();
    }
}
