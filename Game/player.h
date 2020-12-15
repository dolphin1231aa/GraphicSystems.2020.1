#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"

#include <QTimer>

class Player: public QObject{
    Q_OBJECT
public:
    Player(QObject *parent = 0);
    ~Player();
    friend class View;

protected:
    void setGroundY(int);
    void move_horizontal(char);
    void setPositionVertical(char);

    Sprite* getSprite();
    QPoint getPosition();

    int getHeight();
    int getWidth();

    unsigned char getSpeed();
    char getPositionVertical();

protected slots:
    void step();
    void move_vertical();

private:
    Sprite *sprite;

    char position_vertical = 0;

    int playerX = 0;
    int playerY = 0;
    int groundY = 0;

    unsigned char frame_number = 9;
    unsigned char step_number = 5;
    unsigned char position_frame = 0;
    unsigned char speed = 20;

    QPixmap *player_sprite;
    QTimer *timer_step;
    QTimer *timer_jump;
};

#endif // PLAYER_H
