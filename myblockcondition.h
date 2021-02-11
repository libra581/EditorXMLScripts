#ifndef MYBLOCKCONDITION_H
#define MYBLOCKCONDITION_H

#include <QWidget>
#include <QPainter>

class myBlockCondition : public QWidget
{
    Q_OBJECT

private:
    QString text;
    QColor color;
    int count;

public:
    myBlockCondition(int count, QRect, QString, const QColor&, QWidget *parent = nullptr);
    ~myBlockCondition();

    virtual void paintEvent     (QPaintEvent *event);
};

#endif // MYBLOCKCONDITION_H
