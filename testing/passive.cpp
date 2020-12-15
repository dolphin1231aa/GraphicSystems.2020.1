#include "passive.h"

Passive::Passive(QObject *parent) : QObject(parent), QGraphicsItem()
{
    spriteCoffee = new QPixmap(":/coffee.png");  //("Coffee_sprite.png");
    timeCoffee = new QTimer();
    connect(timeCoffee, &QTimer::timeout, this, &Passive::nextFrame);
    timeCoffee->start(250);
    currentFrame=0;
}

Passive::~Passive() { }

QRectF Passive::boundingRect() const {
 return QRectF(-10,-10,100,100);
}

void Passive::nextFrame(){
    currentFrame += 96;
    if (currentFrame >= 320 ) currentFrame = 0;
   // this->update(-10,-10,96,96);
}


void Passive::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option) Q_UNUSED(widget)
    painter->drawPixmap(-10,-10, *spriteCoffee, currentFrame, 0, 96,96);
}
