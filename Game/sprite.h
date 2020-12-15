#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class Sprite: public QObject, public QGraphicsItem
{
public:
    Sprite(QObject *parent = 0);
    Sprite (QPixmap *img, int number);
    ~Sprite();
    friend class Player;
    friend class Croissant;


protected:
    void setFrame(int position);
    void changeImg(QPixmap *img);

protected slots:
    unsigned char nextFrame(unsigned char); // передает параметр позиции картинки спрайта, с которой следует начинать

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRectF boundingRect() const;
    QPixmap *sprite_image;
    int current_frame = 0;   // Координата x, с которой начинает очередной кадр спрайта

    int frame_number;
    int frame_width;
    int frame_height;

};


#endif // SPRITE_H
