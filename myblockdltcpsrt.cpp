#include "myBlockDltCpSrt.h"

myBlockDltCpSrt::myBlockDltCpSrt(QRect rect, QString str, const QColor & color, QWidget *parent)
    :QWidget(parent)
{
    this->text  = str;
    this->color = color;

    this->setStyleSheet("background:  rgba(0, 0, 0, 0);");
    this->setGeometry  ( rect.x(),  rect.y(),  rect.width()+4,  rect.height()+4 );
}

myBlockDltCpSrt::~myBlockDltCpSrt()
{

}

void myBlockDltCpSrt::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin( this );
    painter.setRenderHint   ( QPainter::Antialiasing, true           );
    painter.setPen          ( QPen(color)               );

    painter.drawRect(2, 2, width()-4, height()-20 );
    painter.drawLine( QPoint(width()*0.5,height()-18), QPoint(width()*0.5,height()));
    painter.drawText(QRect(width()*0.2,10,width()-4,height()-20), this->text);

    this->render( &painter, QPoint( 0, 0 ) );

    painter.end( );

    QWidget::paintEvent( event );

}
