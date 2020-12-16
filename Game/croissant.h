#ifndef CROISSANT_H
#define CROISSANT_H

#include "sprite.h"
#include <QTimer>

class Croissant: public QObject{
    Q_OBJECT
public:
    Croissant(QObject *parent = 0);
    Croissant(int, int, int);
    ~Croissant();
    friend class View;

protected:
    void step();
    int getSpeed();

    Sprite *getSprite();
    QTimer *getTimer();
    void setSpeed(int);

    unsigned char frame_number = 9;
    unsigned char step_number = 5;
    unsigned char step_length = 0;

private slots:
    void move();

private:
    Sprite *sprite;

    int croissantX = 0;
    int croissantY = 0;
    int speed;

    unsigned char position_frame = 0;

    QPixmap *croissant_sprite;
    QTimer *timer_step;
    QTimer *timer_move;
};
#endif // CROISSANT_H
