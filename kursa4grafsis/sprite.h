#ifndef SPRITE_H
#define SPRITE_H
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <windows.h>
#include <QKeyEvent>
#include <QDebug>


class sprite : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit sprite(QObject *parent = nullptr);
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QTimer *timer;

private:

    int column =9;
    int w;
    int h;
    int move=0;
    QString state = "B";
    QPixmap *pixmap;
public:signals:
    void udar(QString state);

public slots:
    void Actualizacion();

public slots:
   void keyPressEvent(QKeyEvent *e);

};

#endif // SPRITE_H
