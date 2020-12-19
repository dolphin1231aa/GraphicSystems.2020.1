#include "bg.h"



bg::bg(QObject *parent)
{
    pixmap = new QPixmap(":/naruto/img/PixelArt.png");
    w=1920;
    h=1080;
}

QRectF bg::boundingRect() const
{
    return QRectF(-w/2,-h/2,w,h);
}

void bg::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-w/2,-h/2,*pixmap,0,0,w,h);
}
