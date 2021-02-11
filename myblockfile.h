#ifndef MYBLOCKFILE_H
#define MYBLOCKFILE_H

#include <QWidget>
#include <QPainter>

class myBlockFile : public QWidget
{
    Q_OBJECT
private:
    QString text;
    QColor color;

public:
    explicit myBlockFile(QRect , QString, const QColor&, QWidget *parent = nullptr);
    ~myBlockFile();

    virtual void paintEvent     (QPaintEvent *event);
signals:

public slots:
};

#endif // MYBLOCKFILE_H
