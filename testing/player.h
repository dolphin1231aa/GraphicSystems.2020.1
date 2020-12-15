#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <windows.h>
#include <QTimer>

class Player: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);
    ~Player();

signals:
    void signalCheckItem (QGraphicsItem *item);

public slots:
    void slotMovement();
    void idleChange();


protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void changeStateMove();
   // void changeStateRight();
    void changeStateIdle();

private:
    QPixmap *spritePlayer_right_move;
    QPixmap *spritePlayer_left_move;
    QPixmap *spritePlayer_right_idle;
    QPixmap *spritePlayer_left_idle;
    QTimer *timerIdle;
    int currentFrame;
    int currentFrameIdle=0;
    int statemode=1;
    int delay=0;
    int direction=2;
    int resolution=192;
    int speed=4;

};

#endif // PLAYER_H
