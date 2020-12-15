#ifndef POWERUP_H
#define POWERUP_H

#include "passive.h"
#include <QObject>
#include "player.h"
#include "widget.h"

class PowerupPizza : public Passive
{
    Q_OBJECT
public:
    explicit PowerupPizza(QObject *parent = 0);
    ~PowerupPizza();

signals:

public slots:

private slots:
    void nextFrame();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPixmap *spritePizza;
    QTimer *timePizza;
    int currentFrame;
};

#endif // POWERUP_H
