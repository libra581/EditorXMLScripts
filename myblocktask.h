#ifndef MYBLOCKTASK_H
#define MYBLOCKTASK_H

#include <QWidget>
#include <QPainter>

class myBlockTask : public QWidget
{
    Q_OBJECT
private:
    QString text;
    QColor color;

public:
    explicit myBlockTask(QRect , QString, const QColor&, QWidget *parent = nullptr);

    virtual void paintEvent     (QPaintEvent *event);
signals:

public slots:
};

#endif // MYBLOCKTASK_H
