#include "sprite.h"

Sprite::Sprite(QObject *parent) :
    QObject(parent), QGraphicsItem()
{}


Sprite::Sprite(QPixmap *img, int number) {
    sprite_image = img;
    frame_number = number;
    frame_width = sprite_image->width() / frame_number;
    frame_height = sprite_image->height();
}



QRectF Sprite::boundingRect() const {
    return QRectF(0 , -frame_height - 20, frame_width, frame_height);
}

void Sprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0, -frame_height - 20, *sprite_image, current_frame, 0, frame_width , frame_height);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

unsigned char Sprite::nextFrame(unsigned char position) {
    current_frame += sprite_image->width() / frame_number;
    if (current_frame >= sprite_image->width())  current_frame = position*sprite_image->width() / frame_number;
    this->update();
    return current_frame/(sprite_image->width() / frame_number);
}



void Sprite::setFrame(int position) {
    current_frame = position*sprite_image->width() / frame_number;
    this->update();

}


void Sprite::changeImg(QPixmap *img) {
    sprite_image = img;
}


Sprite::~Sprite() {}

