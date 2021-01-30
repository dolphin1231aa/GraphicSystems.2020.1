#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QMediaPlaylist>

/** Подключаем библиотеку, отвечающую за использование WinAPI
 * Данная библиотека необходима для асинхронной проверки состояния клавиш
 * */
#include <windows.h>

class Triangle : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Triangle(QObject *parent = 0);
    ~Triangle();

signals:
    /** Сигнал, который передаётся в ядро игры с элементом QGraphicsItem,
     * на который наткнулась божья коровка, и требуется принять решение о том,
     * что с этим элементом делать.
     * */
    void signalCheckItem(QGraphicsItem *item);
    void signalSoundStart();
    void signalSoundStop();

public slots:
    void slotGameTimer(); /// Слот, который отвечает за обработку перемещения божьей коровки

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal angle;        /// Угол поворота графического объекта
    int steps;          /// Номер положения ножек божьей коровки
    int countForSteps;  /// Счётчик для отсчета тиков таймера, при которых мы нажимали на кнопки

    QMediaPlayer * m_player;        // Аудио плеер
    QMediaPlaylist * m_playlist;    // Плейлист

};

#endif // TRIANGLE_H
