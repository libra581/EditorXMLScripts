#ifndef MYPLAINTEXTEDIT_H
#define MYPLAINTEXTEDIT_H

#include <QPlainTextEdit>
#include <QTextBlock>
#include <QTextList>
#include <QSyntaxHighlighter>

class myPlainTextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    myPlainTextEdit(QWidget *parent = nullptr);
    bool eventFilter(QObject *object, QEvent *event);



private:
    QString leftToSpace(QString str, int n);
    QString rightToSpace(QString str, int n);

    bool flag_signalEmit = false;
    int postInitBlock = 0;
    QString tempStr = 0;


public slots:
signals:
    void onClickString(QString, int );

};

#endif // MYPLAINTEXTEDIT_H
