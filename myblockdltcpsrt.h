#ifndef MYBLOCKDLTCPSRT_H
#define MYBLOCKDLTCPSRT_H

#include <QWidget>
#include <QPen>
#include <QPainter>

class myBlockDltCpSrt: public QWidget
{
    Q_OBJECT
private:
    QString text;
    QColor color;

public:
    myBlockDltCpSrt(QRect , QString, const QColor&, QWidget *parent = nullptr);
    ~myBlockDltCpSrt();

    virtual void paintEvent     (QPaintEvent *event);
};

#endif // MYBLOCKDLTCPSRT_H
