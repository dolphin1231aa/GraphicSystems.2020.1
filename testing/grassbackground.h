#ifndef GRASSBACKGROUND_H
#define GRASSBACKGROUND_H

#include <QObject>
#include "passive.h"

class grassBackground: public Passive
{
     Q_OBJECT
public:
    explicit grassBackground(QObject *parent = 0);
    ~grassBackground();

private slots:
    void nextFrame();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPixmap *spriteGrass;
    QTimer *timeGrass;
    int currentFrame;
};

#endif // GRASSBACKGROUND_H
