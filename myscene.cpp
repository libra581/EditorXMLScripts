#include "myScene.h"

myScene::myScene(QRectF rect, QObject *parent)
    :QGraphicsScene( rect, parent )
{
    this->setSceneRect(rect.x(), rect.y(), rect.width(), rect.height());
    this->start_Scen_Rect = rect.toRect();
}

myScene::~myScene()
{
    this->clearAllBlocks();
}

void myScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QPen pen;
    pen.setColor( QColor("#413d51") );
    pen.setBrush( QColor("#413d51") );

    painter->setPen  ( pen  );
    painter->setBrush( QBrush( QColor("#413d51") ) );
    painter->drawRect( rect );
}

//Очистка сцены от объектов
void myScene::clearAllBlocks()
{
    foreach (QWidget* ptr, lstAlgth)
    {
        if(ptr)
            delete ptr;

        this->setSceneRect(start_Scen_Rect.x(), start_Scen_Rect.y(), start_Scen_Rect.width(), start_Scen_Rect.height());
    }

    lstAlgth.clear();
}

int myScene::drawBlockScen(int type, const QColor&color)
{
    myBlockScen *blockScenStart;

    if(lstAlgth.isEmpty())
        blockScenStart = new myBlockScen( type, QRect(0, 0, 100, 50), "Scen", Qt::white);
   else
        blockScenStart = new myBlockScen( type, QRect(0, lstAlgth.at(0)->geometry().y()+lstAlgth.at(0)->geometry().height()-1, 100, 50), "Scen", color);
    this->addWidget(blockScenStart);

    lstAlgth.insert(0, blockScenStart);

    this->updateRectScen(50);

    return 0;
}

int myScene::drawBlockDeleteCopyStart(const QString& name, const QColor&color)
{
    myBlockDltCpSrt *blockProc;
    blockProc = new myBlockDltCpSrt(QRect(0, lstAlgth.at(0)->geometry().y()+lstAlgth.at(0)->geometry().height()-1, 100, 50), name, color);

    this->addWidget(blockProc);

    lstAlgth.insert(0, blockProc);

    this->updateRectScen(50);

    return 0;
}

int myScene::drawBlockTask(const QColor&color)
{
    myBlockTask *blockTask;
    blockTask = new myBlockTask(QRect(0, lstAlgth.at(0)->geometry().y()+lstAlgth.at(0)->geometry().height()-1, 100, 50), "Task", color);

    this->addWidget(blockTask);

    lstAlgth.insert(0, blockTask);

    this->updateRectScen(50);

    return 0;
}

int myScene::drawBlockCondition(int count, const QColor & color)
{
    myBlockCondition *blockCondition;
    blockCondition = new myBlockCondition(count, QRect(0, lstAlgth.at(0)->geometry().y()+lstAlgth.at(0)->geometry().height()-1, 100, 50), "Condition", color);

    this->addWidget(blockCondition);

    lstAlgth.insert(0, blockCondition);

    this->updateRectScen(50*count);

    return 0;
}

int myScene::drawBlockFile(const QColor & color)
{
    myBlockFile *blockFile;
    blockFile = new myBlockFile(QRect(0, lstAlgth.at(0)->geometry().y()+lstAlgth.at(0)->geometry().height()-1, 100, 50), "File", color);

    this->addWidget(blockFile);

    lstAlgth.insert(0, blockFile);

    this->updateRectScen(50);

    return 0;
}

void myScene::updateRectScen(int size)
{
    this->setSceneRect(this->sceneRect().x(), this->sceneRect().y(), this->sceneRect().width(), this->sceneRect().height() + size);
}

