#include "shuriken.h"


shuriken::shuriken(QString state,QObject *parent)
{
    timer = new QTimer();
    this->state=state;
    pixmap = new QPixmap(":/naruto/img/shuriken2.png");
    connect(timer,&QTimer::timeout,this,&shuriken::Actualizacion);
     timer->start(100);
     w=44;
     h=28;
     column =0;
}

QRectF shuriken::boundingRect() const
{
    return QRectF(-w/2,-h/2,w,h);
}

void shuriken::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        painter->drawPixmap(-w/2,-h/2,*pixmap,column,0,w,h);
}

void shuriken::Actualizacion()
{
    column +=64;
    if(column >=110)
    {
        column =0;
    }
    if (state == "T"){
       setPos(mapToParent(0,-20));
    }
    if (state == "B"){
        setPos(mapToParent(0,20));
    }
    if (state == "L"){
        setPos(mapToParent(-20,0));
    }
    if (state == "R"){
         setPos(mapToParent(20,0));
    }


    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                             << mapToScene(0, 0)
                                                             << mapToScene(-20, -20)
                                                             << mapToScene(20, -20));

    foreach (QGraphicsItem *item, foundItems) {
           if (item == this)
               continue;
          if(item->type()==228){
           emit destr(item);
              emit selfdstr(this);
                        }
       }



     this->update(-w/2,-h/2,w,h);

}
