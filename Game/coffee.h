#ifndef COFFEE_H
#define COFFEE_H

#include <QObject>
#include <QGraphicsItem>

class Coffee: public QObject, public QGraphicsItem {
public:
    Coffee(QObject *parent = 0);
    Coffee (QPixmap *img);
    friend class View;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QPixmap *image;
};

#endif // COFFEE_H
