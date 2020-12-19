#include "sprite.h"


sprite::sprite(QObject *parent) : QObject(parent)
{

 timer = new QTimer();
 pixmap = new QPixmap(":/naruto/img/naruto.png");
 connect(timer,&QTimer::timeout,this,&sprite::Actualizacion);
 timer->start(100);
 w=18;
 h=32;

}

QRectF sprite::boundingRect() const
{
    return QRectF(-9,-16,18,32);
}


void sprite::Actualizacion()
{


    if(GetAsyncKeyState('A')||GetAsyncKeyState('W') ||GetAsyncKeyState('S')||GetAsyncKeyState('D')){

    column +=19;
    if(column >=80)
    {
        column =10;
    }
}else {
        column=10;
    }

    if(GetAsyncKeyState('A')){
         setPos(mapToParent(-5,0));
         move =38;
         state = 'L';
    }
      if(GetAsyncKeyState('D')){
         setPos(mapToParent(5,0));
          move =38*2;
           state = 'R';

      }
      if(GetAsyncKeyState('W')){
          setPos(mapToParent(0,-5));
           move =38*3;
            state = 'T';

      }
      if(GetAsyncKeyState('S')){

      setPos(mapToParent(0,5));
      move =0;
       state = 'B';
      }
      if (GetAsyncKeyState(VK_SPACE)){
           emit udar(state);
      }

    this->update(-18/2,-32/2,30,32);





}

void sprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-18/2,-32/2,*pixmap,column,11+move,18,32);
}

 void sprite::keyPressEvent(QKeyEvent *e)
{
     qDebug()<<"kek1";
     e->accept();
    if(e->key()==Qt::Key_Space) {

        qDebug()<<"kek";
        emit udar(state);

    }
}

