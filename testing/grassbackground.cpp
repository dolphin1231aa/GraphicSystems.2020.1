#include "grassbackground.h"


grassBackground::grassBackground(QObject *parent)
{
    spriteGrass = new QPixmap(":/grass.png");  //("Coffee_sprite.png");
    timeGrass = new QTimer();
    connect(timeGrass, &QTimer::timeout, this, &grassBackground::nextFrame);
    timeGrass->start(150);
    currentFrame=0;
}

grassBackground::~grassBackground() { }

QRectF grassBackground::boundingRect() const {
 return QRectF(0,0,32,32);// Ограничиваем область, в которой лежит яблоко
}

void grassBackground::nextFrame(){
    currentFrame += 32;
    if (currentFrame >= 384 ) currentFrame = 0;
   // this->update(-10,-10,96,96);
}


void grassBackground::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option) Q_UNUSED(widget) //Пока не используем эти параметры
    painter->drawPixmap(0,0, *spriteGrass, currentFrame, 0, 32,32);
}
