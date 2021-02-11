#ifndef MYSCENE_H
#define MYSCENE_H


#include <QGraphicsScene>
#include <QPainter>

#include "myblockscen.h"
#include "myblocktask.h"
#include "myblockdltcpsrt.h"
#include "myblockcondition.h"
#include "myblockfile.h"

class myScene : public QGraphicsScene
{
    Q_OBJECT
private:
    QList<QWidget*> lstAlgth;   //Набор виджетов созданных на сцене по сценарию
    QRect start_Scen_Rect;

public:
    explicit myScene(QRectF rect, QObject *parent = nullptr);
    ~myScene();

protected:
    virtual void drawBackground         (QPainter *painter, const QRectF &rect   ) override;

public slots:
    void clearAllBlocks();
    //Слоты отрисовки блоков алгоритма по видам тегов
    int drawBlockScen(int type, const QColor&);
    int drawBlockDeleteCopyStart(const QString &name, const QColor&);
    int drawBlockTask(const QColor&);
    int drawBlockCondition(int count, const QColor&);
    int drawBlockFile(const QColor & color);

private:
    void updateRectScen(int size);
};

#endif // MYSCENE_H
