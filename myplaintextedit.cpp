#include "myplaintextedit.h"

myPlainTextEdit::myPlainTextEdit(QWidget *parent):
    QPlainTextEdit(parent)
{
    installEventFilter(this);

}

bool myPlainTextEdit::eventFilter(QObject *object, QEvent *event)
{

     if(object == this && event->type() == QEvent::InputMethodQuery)
     {
         QInputMethodQueryEvent *inputEvent = static_cast<QInputMethodQueryEvent *>(event);

         QString str = leftToSpace(this->textCursor().block().text(), this->textCursor().positionInBlock()) +
                 rightToSpace(this->textCursor().block().text(), this->textCursor().positionInBlock());

         if(tempStr != str )
         {
             tempStr = str;
             flag_signalEmit = false;
         }
         else if(postInitBlock != this->textCursor().blockNumber() )
         {
             postInitBlock = this->textCursor().blockNumber();

             if(inputEvent->queries()==Qt::ImEnabled)
                emit onClickString(tempStr, this->textCursor().blockNumber());
         }

         if(!tempStr.isEmpty() && !flag_signalEmit )
         {
             flag_signalEmit = true;
             emit onClickString(tempStr, this->textCursor().blockNumber());
             QString strTemp=tempStr;
             postInitBlock = this->textCursor().blockNumber();
         }
         return true;
     }
     return false;
}

QString myPlainTextEdit::leftToSpace(QString str, int n)
{
    QString temp_str;

      for(int i = n-1; (i >= 0) && (str.at(i) != ' '); i--)
          temp_str.prepend(str.at(i));

    return temp_str;
}

QString myPlainTextEdit::rightToSpace(QString str, int n)
{
    QString temp_str;

    for(int i = n; (i <= str.length()-1) && (str.at(i) != ' ') ; i++)
        temp_str.append(str.at(i));

    return temp_str;
}


