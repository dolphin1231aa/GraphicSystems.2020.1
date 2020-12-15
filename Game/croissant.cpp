#include "croissant.h"

Croissant::Croissant(QObject *parent) :
    QObject(parent)
{}

Croissant::Croissant(int croissantX, int croissantY, int speed) {
    croissant_sprite = new QPixmap(":/sprite/croissant-right.png");

    this->croissantX = croissantX;
    this->croissantY = croissantY;
    this->speed = speed;

    sprite = new Sprite(croissant_sprite, frame_number);
    step_length = croissant_sprite->width()/frame_number;
    sprite->setPos(croissantX, croissantY);

    timer_move = new MyTimer();
    connect(timer_move, SIGNAL(my_timeout(char)), this , SLOT(move(char)));

    timer_step = new QTimer();
    connect(timer_step, &QTimer::timeout, this, &Croissant::step);
}


void Croissant::move(char side) {
    if (side == 1) sprite->changeImg(new QPixmap(":/sprite/croissant-right.png"));
    if (side == -1) sprite->changeImg(new QPixmap(":/sprite/croissant-left.png"));
    position_frame = sprite->nextFrame(1);
    sprite->setPos(croissantX += side*speed, croissantY);
}

void Croissant::step() {
    if (position_frame <= step_number) {
        if (position_frame == step_number)  {
            timer_step->stop();
            sprite->setFrame(0);
        } else  position_frame = sprite->nextFrame(0);

    } else {
        if (position_frame == frame_number-1) {
            timer_step->stop();
            sprite->setFrame(0);
        } else position_frame = sprite->nextFrame(step_number);
    }
}


Sprite* Croissant::getSprite() {
    return sprite;
}

MyTimer* Croissant::getTimer() {
    return timer_move;
}

Croissant:: ~Croissant() {
}
