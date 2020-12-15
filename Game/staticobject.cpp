#include "staticobject.h"

StaticObject::StaticObject(QObject *parent) :
    QObject(parent), QGraphicsItem()
{}


StaticObject::StaticObject(QPixmap *img) {
    this->img = img;
}

QRectF StaticObject::boundingRect() const {
    return QRectF(0, -20 , img->width(), img->height());
}

void StaticObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0, -20 , *img, 0, 0, img->width(), img->height());
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
