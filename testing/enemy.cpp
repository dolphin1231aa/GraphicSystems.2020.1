#include "enemy.h"
#include "widget.h"

Enemy::Enemy(QGraphicsItem *target, QObject *parent) : QObject(parent), QGraphicsItem() {
    this->target = target;
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Enemy::slotGameTimer);
    timer->start (20);
    enemyLeftSprite = new QPixmap (":/Enemy_left.png");
    enemyRightSprite = new QPixmap (":/Enemy_right.png");
}

Enemy::~Enemy(){}

QRectF Enemy::boundingRect() const {
 //return QRectF(0,0,192,192);
 return QRectF(0,-100,192,192);
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option) Q_UNUSED(widget)
     switch (stateMovement) {
        case 1:
            painter->drawPixmap(0,0, *enemyLeftSprite, currentFrame, 0, resolution,resolution);
            break;
        case 0:
            painter->drawPixmap(0,0, *enemyRightSprite, currentFrame, 0, resolution,resolution);
            break;
    }
}

void Enemy::changeStateMove(){
    delay++;
    switch (statemode) {
    case 1:
        if(delay==5){
            currentFrame=2*resolution;statemode=2;delay=0;
        }
        break;
    case 2:
        if(delay==5){
            currentFrame=3*resolution;statemode=3;delay=0;
        }
        break;
    case 3:
        if(delay==5){
            currentFrame=4*resolution;statemode=4;delay=0;
        }
        break;
    case 4:
        if(delay==5){
            currentFrame=5*resolution;statemode=5;delay=0;
        }
        break;
    case 5:
        if(delay==5){
            currentFrame=6*resolution;statemode=6;delay=0;
        }
        break;
    case 6:
        if(delay==5){
            currentFrame=7*resolution;statemode=7;delay=0;
        }
        break;
    case 7:
        if(delay==5){
            currentFrame=0*resolution;statemode=8;delay=0;
        }
        break;
    case 8:
        if(delay==5){
            currentFrame=1*resolution;statemode=1;delay=0;
        }
        break;
    }
}

void Enemy::slotGameTimer() {
    speed=Settings::speed_enemy;
    QLineF lineToTarget (QPointF(0, 0), mapFromItem(target, 0, 0));
        changeStateMove();
        if (lineToTarget.dx()<0){
            setPos(mapToParent(-speed,0));
            stateMovement=1;
        }
        if (lineToTarget.dy()<0){
            setPos(mapToParent(0,-speed));
        }
        if (lineToTarget.dx()>0){
            setPos(mapToParent(speed,0));
            stateMovement=0;
        }
        if (lineToTarget.dy()>0){
            setPos(mapToParent(0,speed));
        }
    //update(QRectF(-40,-50,80,100));
    QList <QGraphicsItem *> foundItems = scene()->items(QPolygonF()
     << mapToScene(50, 50)
     << mapToScene(50, 50)
     << mapToScene(50, 50));
    /*QList <QGraphicsItem *> foundItems = scene()->items(QPolygonF()
     << mapToScene(96, 96)
     << mapToScene(96, 96)
     << mapToScene(96, 96));*/

    foreach (QGraphicsItem *item, foundItems) {
     if (item == this) continue;
     if (item == target) {
      emit signalCheckGameOver();
     }
    }


    /*if (this->x() - 10 < -250) {
     this->setX(-240);
    }
    if(this->x() + 10 > 250){
     this->setX(240);
    }
    if(this->y() - 10 < -250){
     this->setY(-240);
    }
    if(this->y() + 10 > 250){
     this->setY(240);
    }*/
}
