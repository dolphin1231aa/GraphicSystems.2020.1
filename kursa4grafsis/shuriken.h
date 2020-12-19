#ifndef SHURIKEN_H
#define SHURIKEN_H
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsScene>
#include <grob.h>
#include <QObject>
#include <QDebug>

class shuriken : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit shuriken(QString state,QObject *parent = nullptr);
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QTimer *timer;

private:
    int column =9;
    int w;
    int h;
    QString state;
    //int move=0;


    QPixmap *pixmap;
public: signals:
     void destr(QGraphicsItem *obj);
     void selfdstr(QGraphicsItem *obj);
public slots:
    void Actualizacion();

};

#endif // SHURIKEN_H
