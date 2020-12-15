#ifndef VIEW_H
#define VIEW_H

#include "player.h"
#include "croissant.h"
#include "staticobject.h"

#include <QWidget>
#include <QGraphicsView>
#include <QLabel>
#include <QFontDatabase>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QKeyEvent>
#include <QTime>
#include <QDir>
#include <QMessageBox>

class View : public QGraphicsView
{
public:
    explicit View(QWidget *parent = 0);
    ~View();

private slots:
    void gameTimer();
    void gameMove();
    void deleteItem (QGraphicsItem *);
    void deleteAllItem (QList<QGraphicsItem *>&);

    QList<QGraphicsItem *> coffee_list;
    QList<QGraphicsItem *> croissant_list;
    QList<QGraphicsItem *> platform_list;

    QList<Croissant *> croissants;

private:
    void gameStart();
    void createCoffee();
    void createCroissant();
    void createPlatform();
    void gameOver(char);
    void findPlatform(QList<QGraphicsItem *>, QList<QGraphicsItem *>);
    void setFrame();

    Player* player;

    QVector <int> itm_positionY;

    int x = 0;
    int y = 0;
    int const minX = 0;
    int const maxX = 15000;

    char move_side = 0;

    unsigned char coffeeMax = 20;
    unsigned char croissantMax = 36;
    unsigned char platformMax = 80;
    unsigned char coffee_score = 0;
    unsigned char croissant_score = 0;
    unsigned char coffee_combination;
    unsigned char croissant_combination;
    unsigned char randomSpeed();

    QPoint randomPos(unsigned int, unsigned int, int);

    QGraphicsScene* scene;
    QGraphicsTextItem* textItem;

    QPixmap *coffee_img;
    QPixmap *croissant_img;
    QPixmap *platform_img;

    QLabel *lbl_coffee;
    QLabel *lbl_croissant;
    QLabel *lbl_croissant_score;
    QLabel *lbl_coffee_score;
    QLabel *lbl_title;

    QFrame *frame;

    QTimer *timer_game;
    QTimer *timer_move;

    QMediaPlayer *m_music;
    QMediaPlayer *m_sounds;
    QMediaPlaylist *m_playlist_croissant;
    QMediaPlaylist *m_playlist_background;
    QMediaPlaylist *m_playlist_death;
};

#endif // VIEW_H
