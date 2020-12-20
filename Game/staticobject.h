#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class StaticObject: public QObject, public QGraphicsItem {
public:
    StaticObject(QObject *parent = 0);
    StaticObject (QPixmap *img);
    friend class View;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRectF boundingRect() const;
    QPixmap *img;
};

#endif // STATICOBJECT_H
