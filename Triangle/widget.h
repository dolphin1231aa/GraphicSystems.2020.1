#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QShortcut>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <triangle.h>
#include <apple.h>
#include <spider.h>

#define GAME_STOPED 0
#define GAME_STARTED 1

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget      *ui;
    QGraphicsScene  *scene;     /// Объявляем графическую сцену
    Triangle        *triangle;  /// и треугольник
    QTimer          *timer;     /** Объявляем игровой таймер, благодаря которому
                                 * будет производиться изменения положения объекта на сцене
                                 * При воздействии на него клавишами клавиатуры
                                 * */
    QTimer          *timerCreateApple;  /// Таймер для периодического создания яблок в игре

    QList<QGraphicsItem *> apples;  /// Список со всеми яблоками, присутствующими в игре
    double count;   /// Переменная, которая хранит счёт игре

    Spider          *spider;        // Объект Паука

    QShortcut       *pauseKey;      // Горячая клавиша, отвечающая за паузу в игре
    int             gameState;      /* Переменная, которая хранит состояние игры.
                                     * То есть, если игра запущена, то статус будет GAME_STARTED,
                                     * в противном случае GAME_STOPED
                                     * */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private slots:
    /// Слот для удаления яблок если божья коровка наткнулась на это яблоко
    void slotDeleteApple(QGraphicsItem * item);
    void slotCreateApple();     /// Слот для создания яблок, срабатывает по таймеру

    void on_pushButton_clicked();               // Слот для запуска игры
    void slotGameOver();                        // Слот инициализации Game Over
    void slotPause();                           // Слот для обработки паузы
};

#endif // WIDGET_H
