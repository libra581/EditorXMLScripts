#ifndef MYBLOCKSCEN_H
#define MYBLOCKSCEN_H

#include <QWidget>
#include <QPen>
#include <QPainter>

class myBlockScen : public QWidget
{
    Q_OBJECT

private:
    QString text;
    QColor color;
    int type;


public:
    explicit myBlockScen(int type, QRect , QString, const QColor&, QWidget *parent = nullptr);
    ~myBlockScen();

    virtual void paintEvent     (QPaintEvent *event);

signals:

public slots:
};

#endif // MYBLOCKSCEN_H
