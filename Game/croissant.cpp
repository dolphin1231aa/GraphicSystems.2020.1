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

    timer_move = new QTimer();
    connect(timer_move, &QTimer::timeout, this , &Croissant::move);

    timer_step = new QTimer();
    connect(timer_step, &QTimer::timeout, this, &Croissant::step);
}


void Croissant::move() {
    if (speed > 0) sprite->changeImg(new QPixmap(":/sprite/croissant-right.png"));
    if (speed < 0) sprite->changeImg(new QPixmap(":/sprite/croissant-left.png"));
    position_frame = sprite->nextFrame(1);
    sprite->setPos(croissantX += speed, croissantY);
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

void Croissant::setSpeed(int speed) {
    this->speed = speed;
}

Sprite* Croissant::getSprite() {
    return sprite;
}

int Croissant::getSpeed() {
    return speed;
}

QTimer *Croissant::getTimer() {
    return timer_move;
}

Croissant:: ~Croissant() {
}
