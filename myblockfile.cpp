#include "myBlockFile.h"

myBlockFile::myBlockFile(QRect rect, QString str, const QColor &color, QWidget *parent)
    : QWidget(parent)
{
    this->text  = str;
    this->color = color;

    this->setStyleSheet("background:  rgba(0, 0, 0, 0);");
    this->setGeometry  ( rect.x(),  rect.y(),  rect.width()+4,  rect.height()+4 );
}

myBlockFile::~myBlockFile()
{

}

void myBlockFile::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin( this );
    painter.setRenderHint   ( QPainter::Antialiasing, true           );
    painter.setPen          ( QPen(color)               );

    painter.drawLine( QPoint(0+20,0), QPoint(width(),0));
    painter.drawLine( QPoint(0,height()-19), QPoint(width()-20,height()-19));
    painter.drawLine( QPoint(0+20,0), QPoint(x(),height()-19));
    painter.drawLine( QPoint(width(),0), QPoint(width()-20,height()-19));
    painter.drawText(QRect(width()*0.2,10,width()-4,height()-20), this->text);
    painter.drawLine( QPoint(width()*0.5,height()-18), QPoint(width()*0.5,height()));

    this->render( &painter, QPoint( 0, 0 ) );

    painter.end( );

    QWidget::paintEvent( event );
}
