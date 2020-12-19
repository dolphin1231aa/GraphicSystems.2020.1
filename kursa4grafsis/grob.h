#ifndef GROB_H
#define GROB_H
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <windows.h>


class grob : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit grob(QObject *parent = nullptr);
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QTimer *timer;
    virtual int type() const override;

private:

    int column =0;
    int w;
    int h;
    QPixmap *pixmap;
private slots:
    void dstrslot();

public slots:

    void Actualizacion();

};
#endif // GROB_H
