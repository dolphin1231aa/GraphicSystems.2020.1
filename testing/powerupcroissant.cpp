#include "powerupcroissant.h"
#include "widget.h"


PowerupCroissant::PowerupCroissant(QObject *parent) //: QObject(parent), QGraphicsItem()
{
    spriteCroissant = new QPixmap(":/croissant.png");  //("Coffee_sprite.png");
    timeCroissant = new QTimer();
    connect(timeCroissant, &QTimer::timeout, this, &PowerupCroissant::nextFrame);
    timeCroissant->start(250);
    currentFrame=0;
}

PowerupCroissant::~PowerupCroissant() {
    Settings::speed_enemy=1;
}

QRectF PowerupCroissant::boundingRect() const {
 return QRectF(-10,-10,100,100);
}

void PowerupCroissant::nextFrame(){
    currentFrame += 96;
    if (currentFrame >= 768 ) currentFrame = 0;
}

void PowerupCroissant::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option) Q_UNUSED(widget)
    painter->drawPixmap(0,0, *spriteCroissant, currentFrame, 0, 96,96);
}
