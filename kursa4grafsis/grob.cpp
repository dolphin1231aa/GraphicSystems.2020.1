#include "grob.h"


grob::grob(QObject *parent)
{
    timer = new QTimer();
    pixmap = new QPixmap(":/naruto/img/grob.png");
    connect(timer,&QTimer::timeout,this,&grob::Actualizacion);
    timer->start(400);
    w=86;
    h=100;
}

QRectF grob::boundingRect() const
{
    return QRectF(-w/2,-h/2,w,h);
}

void grob::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-w/2,-h/2,*pixmap,column,0,w,h);
}

int grob::type() const
{
    return 228;
}




void grob::dstrslot()
{
    if(column >360)
    {
        column +=79;

    }else{
    timer->stop();
    disconnect(timer,&QTimer::timeout,this,&grob::Actualizacion);
    }
}

void grob::Actualizacion()
{

    if(column <360)
    {
        column +=79;

    }else{
    timer->stop();
    disconnect(timer,&QTimer::timeout,this,&grob::Actualizacion);
    }
     this->update(-w/2,-h/2,w,h);
}
