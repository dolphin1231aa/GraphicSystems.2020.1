#include "player.h"
#include "widget.h"
#include <qDebug>

Player::Player(QObject *parent) :  QObject(parent), QGraphicsItem()
{
    spritePlayer_left_move = new QPixmap(":/Player_left_move.png");
    spritePlayer_left_idle = new QPixmap(":/Player_left_idle.png");
    spritePlayer_right_move = new QPixmap(":/Player_right_move.png");
    spritePlayer_right_idle = new QPixmap(":/Player_right_idle.png");
    currentFrame=2*resolution;
    timerIdle = new QTimer();
    connect(timerIdle, &QTimer::timeout, this, &Player::idleChange);
    timerIdle->start(250);

}

Player::~Player(){}

void Player::idleChange(){
    currentFrameIdle += resolution;
    if (currentFrameIdle >= 2*resolution ) currentFrameIdle = 0;
}

void Player::slotMovement(){
    speed=Settings::speed_player;
    if (GetAsyncKeyState(VK_LEFT) ||
            GetAsyncKeyState(VK_RIGHT) ||
            GetAsyncKeyState(VK_UP) ||
            GetAsyncKeyState(VK_DOWN)) {
        if ((GetAsyncKeyState(VK_UP))&&(GetAsyncKeyState(VK_RIGHT))){
            setPos(mapToParent(speed, 0));
            setPos(mapToParent(0, -speed));
            direction=3;
            changeStateMove();
        }else{
            if ((GetAsyncKeyState(VK_DOWN))&&(GetAsyncKeyState(VK_RIGHT))){
                setPos(mapToParent(0, speed));
                setPos(mapToParent(speed, 0));
                direction=3;
                changeStateMove();
            }else{
                if ((GetAsyncKeyState(VK_DOWN))&&(GetAsyncKeyState(VK_LEFT))){
                    setPos(mapToParent(0, speed));
                    setPos(mapToParent(-speed, 0));
                    direction=1;
                    changeStateMove();
                }else{
                    if ((GetAsyncKeyState(VK_UP))&&(GetAsyncKeyState(VK_LEFT))){
                        setPos(mapToParent(0, -speed));
                        setPos(mapToParent(-speed, 0));
                        direction=1;
                        changeStateMove();
                    }else{
                        if(GetAsyncKeyState(VK_LEFT)) {
                            setPos(mapToParent(-speed, 0));
                            direction=1;
                            changeStateMove();
                        }
                        if(GetAsyncKeyState(VK_RIGHT)) {
                            setPos(mapToParent(speed, 0));
                            direction=3;
                            changeStateMove();
                        }
                        if(GetAsyncKeyState(VK_UP)) {
                            setPos(mapToParent(0, -speed));
                            if ((direction==1)||(direction==2)){
                                direction=1;
                                changeStateMove();
                            }
                            if ((direction==3)||(direction==4)){
                                direction=3;
                                changeStateMove();
                            }
                        }
                        if(GetAsyncKeyState(VK_DOWN)) {
                            setPos(mapToParent(0, speed));
                            if ((direction==1)||(direction==2)){
                                direction=1;
                                changeStateMove();
                            }
                            if ((direction==3)||(direction==4)){
                                direction=3;
                                changeStateMove();
                            }
                        }
                    }
                }
            }
        }
        //this->update(-10,-10,96,96);
        //update(QRectF(-40,-50,80,100));
    }else{
        changeStateIdle();
    }
    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
      << mapToScene(100, 100)
      << mapToScene(100, 100)
      << mapToScene(100, 100)); //начинает с верхней левой точки квадратом?

    foreach (QGraphicsItem *item, foundItems) {
     if (item == this) continue;
     emit signalCheckItem(item);
    }
    if (this->x() - 10 < -680) {
        this->setX(-670);
    }
    if (this->x() + 10 > 510) {
        this->setX(500);
    }
    if (this->y() - 10 < -580) {
        this->setY(-570);
    }
    if (this->y() + 10 > 360) {
        this->setY(350);
    }
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option) Q_UNUSED(widget)
    switch (direction) {
    case 1:
        painter->drawPixmap(0,0, *spritePlayer_left_move, currentFrame, 0, resolution, resolution);

        break;
    case 2:
        painter->drawPixmap(0,0, *spritePlayer_left_idle, currentFrameIdle, 0, resolution, resolution);

        break;
    case 3:
        painter->drawPixmap(0,0, *spritePlayer_right_move, currentFrame, 0, resolution, resolution);

        break;
    case 4:
        painter->drawPixmap(0,0, *spritePlayer_right_idle, currentFrameIdle, 0, resolution, resolution);

        break;
    }
    //qDebug() << this->pos();
}


QRectF Player::boundingRect() const {
    return QRectF( 0, 0, resolution/2, resolution/2);
    //return QRectF( 0, 0, resolution/2, resolution/2); более менее
    //return QRectF( 0, -100, resolution, resolution);
}

void Player::changeStateMove(){
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
/*
void Player::changeStateRight(){
    test++;
    /*switch (statemode) {
    case 1:
        if(test==5){
            currentFrame=resolution;statemode=2;test=0;
        }
        break;
    case 2:
        if(test==5){
            currentFrame=2*resolution;statemode=3;test=0;
        }
        break;
    case 3:
        if(test==5){
            currentFrame=3*resolution;statemode=1;test=0;
        }
        break;
    }*/
   /* test++;
    switch (statemode) {
    case 1:
        if(test==5){
            currentFrame=2*resolution;statemode=2;test=0;
        }
        break;
    case 2:
        if(test==5){
            currentFrame=3*resolution;statemode=3;test=0;
        }
        break;
    case 3:
        if(test==5){
            currentFrame=4*resolution;statemode=4;test=0;
        }
        break;
    case 4:
        if(test==5){
            currentFrame=5*resolution;statemode=5;test=0;
        }
        break;
    case 5:
        if(test==5){
            currentFrame=6*resolution;statemode=6;test=0;
        }
        break;
    case 6:
        if(test==5){
            currentFrame=7*resolution;statemode=7;test=0;
        }
        break;
    case 7:
        if(test==5){
            currentFrame=0*resolution;statemode=8;test=0;
        }
        break;
    case 8:
        if(test==5){
            currentFrame=1*resolution;statemode=1;test=0;
        }
        break;
    }
}
*/
void Player::changeStateIdle(){
    if (direction==1){
        direction=2;
    }
    if (direction==3){
        direction=4;
    }
}
