#include "myBlockCondition.h"

myBlockCondition::myBlockCondition(int count, QRect rect, QString str, const QColor & color, QWidget *parent)
    : QWidget(parent)
{
    this->text  = str;
    this->color = color;
    this->count = count;

    this->setStyleSheet("background:  rgba(0, 0, 0, 0);");
    this->setGeometry( rect.x(),  rect.y(),  rect.width()*count+4,  rect.height()*3+4 );
}

myBlockCondition::~myBlockCondition()
{

}

void myBlockCondition::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin( this );
    painter.setRenderHint   ( QPainter::Antialiasing, true           );
    painter.setPen          ( QPen(color)               );

    painter.drawLine( QPoint(width()/count*0.5+2, 2), QPoint(width()/count-2, height()/3*0.5) );
    painter.drawLine( QPoint(width()/count*0.5+2, 2), QPoint(2, height()/3*0.5) );
    painter.drawLine( QPoint(width()/count*0.5, height()/3+2), QPoint(2, height()/3*0.5) );
    painter.drawLine( QPoint(width()/count*0.5, height()/3+2), QPoint(width()/count, height()/3*0.5+2) );

    int pprvk = 10;

    painter.drawLine( QPoint(width()/count*0.5, height()/3-18+pprvk+10), QPoint(width()/count*0.5, height()+pprvk));
    painter.drawLine( QPoint(width()/count-1, height()/3*0.35+pprvk), QPoint(width()/count+19, height()/3*0.35+pprvk));

    for (int hg = (height()/3*0.35+pprvk), i = 0; i < count; ++i, hg+=50)
    {
        if(i<count-1)
        {
            painter.drawLine( QPoint(width()/count+9, hg), QPoint(width()/count+9, hg+49));
            painter.drawLine( QPoint(width()/count+9, hg+49), QPoint(width()/count+19, hg+49));
        }
        painter.drawRect( width()/count+20 , 2 + 50*i +pprvk, width()/count-4, height()/3-20  );
    }

    painter.drawText(QRect(width()/count*0.3,20,width()/count-4,height()/3-20), this->text);

    this->render( &painter, QPoint( 0, 0 ) );

    painter.end( );

    QWidget::paintEvent( event );
}
