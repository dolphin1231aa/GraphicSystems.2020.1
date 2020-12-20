#include "poweruppizza.h"
#include "widget.h"


PowerupPizza::PowerupPizza(QObject *parent) //: QObject(parent), QGraphicsItem()
{
    spritePizza = new QPixmap(":/pizza.png");  //("Coffee_sprite.png");
    timePizza = new QTimer();
    connect(timePizza, &QTimer::timeout, this, &PowerupPizza::nextFrame);
    timePizza->start(250);
    currentFrame=0;
}

PowerupPizza::~PowerupPizza() {
    Settings::speed_player=8;
}

QRectF PowerupPizza::boundingRect() const {
 return QRectF(-10,-10,100,100);
}

void PowerupPizza::nextFrame(){
    currentFrame += 70;
    if (currentFrame >= 420 ) currentFrame = 0;
   // this->update(-10,-10,96,96);
}/**/

void PowerupPizza::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option) Q_UNUSED(widget)
    painter->drawPixmap( 0, 0, *spritePizza, currentFrame, 0, 70,70);
}
