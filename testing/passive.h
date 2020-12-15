#ifndef PASSIVE_H
#define PASSIVE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>

class Passive : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Passive(QObject *parent = 0);
    ~Passive();

signals:

public slots:

private slots:
    void nextFrame();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPixmap *spriteCoffee;
    QTimer *timeCoffee;
    int currentFrame;
};


#endif // PASSIVE_H
