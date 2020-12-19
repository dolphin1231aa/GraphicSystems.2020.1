#ifndef BG_H
#define BG_H
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <windows.h>

class bg : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit bg(QObject *parent = nullptr);
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


private:

    int w;
    int h;
    QPixmap *pixmap;

};
#endif // BG_H
