#ifndef POWERUPCROISSANT_H
#define POWERUPCROISSANT_H

#include "passive.h"
#include <QObject>
#include "widget.h"

class PowerupCroissant : public Passive
{
    Q_OBJECT
public:
    explicit PowerupCroissant(QObject *parent = 0);
    ~PowerupCroissant();

signals:

public slots:

private slots:
    void nextFrame();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPixmap *spriteCroissant;
    QTimer *timeCroissant;
    int currentFrame;
};

#endif // POWERUPCROISSANT_H
