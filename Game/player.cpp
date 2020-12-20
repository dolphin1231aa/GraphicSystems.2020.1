#include "player.h"

#include <QDebug>
Player::Player(QObject *parent) :
    QObject(parent)
{

    player_sprite = new QPixmap(":/sprite/player-right.png");
    sprite = new Sprite(player_sprite, frame_number);

    timer_step = new QTimer();
    timer_jump = new QTimer();

    connect(timer_step, &QTimer::timeout, this, &Player::step);
    connect(timer_jump, &QTimer::timeout, this, &Player::move_vertical);

    sprite->setPos(playerX, playerY);

}

void Player::move_horizontal() {
    if (speed > 0)  sprite->changeImg(new QPixmap(":/sprite/player-right.png"));
    if (speed < 0) sprite->changeImg(new QPixmap(":/sprite/player-left.png"));
    sprite->setPos(playerX += speed, playerY);
    position_frame = sprite->nextFrame(1);
    (position_frame != frame_number-1 || position_frame != step_number) ? timer_step->start(140) : timer_step->stop();
}

void Player::step() {
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

void Player::move_vertical() {
    int ms = 16;
    if (position_vertical == 1 || position_vertical == 0) {
        position_vertical = 1;
        sprite->setPos(playerX, playerY -= 20);
        ms = 20;
    } else {
        position_vertical = -1;
        sprite->setPos(playerX, playerY += 20);
        ms = 22;
    }
    if (playerY <= -player_sprite->height() + groundY)  position_vertical = -1;
    if (playerY >= groundY)  position_vertical = 0;
    if (position_vertical != 0) timer_jump->start(ms);
    else  {
        timer_jump->stop();
        position_vertical = 0;
    }

}

void Player::setPositionVertical(char position_vertical) {
    this->position_vertical = position_vertical;
}

void Player::setGroundY(int groundY){
    this->groundY = groundY;
}

void Player::setSpeed(int speed) {
    this->speed = speed;
}

Sprite* Player::getSprite() {
    return sprite;
}

QPoint Player::getPosition(){
    return QPoint (playerX, playerY);
}


char Player::getPositionVertical() {
    return position_vertical;
}

int Player::getHeight() {
    return player_sprite->height();
}

int Player::getWidth() {
    return player_sprite->width() / frame_number;
}

int Player::getSpeed() {
    return speed;
}


Player::~Player() {
    timer_jump->stop();
    timer_step->stop();
}
