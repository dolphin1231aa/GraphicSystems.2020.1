#ifndef CROISSANT_H
#define CROISSANT_H

#include "sprite.h"
#include "mytimer.h"

class Croissant: public QObject{
    Q_OBJECT
public:
    Croissant(QObject *parent = 0);
    Croissant(int, int, int);
    ~Croissant();
    friend class View;

protected:
    void step();

    Sprite *getSprite();
    MyTimer *getTimer();

    unsigned char frame_number = 9;
    unsigned char step_number = 5;
    unsigned char step_length = 0;

private slots:
    void move(char);

private:
    Sprite *sprite;
    MyTimer *timer_move;

    int croissantX = 0;
    int croissantY = 0;

    unsigned char position_frame = 0;
    unsigned char speed = 10;

    QPixmap *croissant_sprite;
    QTimer *timer_step;
};
#endif // CROISSANT_H
