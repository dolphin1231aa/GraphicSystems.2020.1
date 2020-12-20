#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDesktopWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "passive.h"
#include "player.h"
#include "enemy.h"
#include "poweruppizza.h"
#include "powerupcroissant.h"
#include "QLabel"
#include "grassbackground.h"
#include <QFontDatabase>

#define MAXGRASS 150
#define MAX 10
#define MAXENEMY 4

namespace Ui { class Widget; }

class Widget : public QWidget {
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


private:
    Ui::Widget      *ui;
    QGraphicsScene  *scene;
    QTimer          *timerMovement;
    Player *player;
    Enemy *enemy1;
    Enemy *enemy2;
    QTimer          *timerCreatePassive;
    QList<QGraphicsItem *> passiveList;
    QTimer *timerUpdate;
   // QTimer *timerCreateEnemy;
    //QList<QGraphicsItem *> enemyList;
    int enemyPosition;
    //QList<Enemy*> enemyListObj;
    QTimer *timerPowerup;
    QList<QGraphicsItem *> powerupPizzaList;
    QList<QGraphicsItem *> powerupCroissantList;
    QTimer *timerPowerupLastingPizza;
    QTimer *timerPowerupLastingCroissant;
    QString speed_target;
    QLabel *totalScoreLabel;
    int totalScore;
    void CreateEnemy();
    bool gamestate=0;
    void AddGrass();
    QList<QGraphicsItem *> grassList;
    QMediaPlayer *backgroundPlayer;
    QMediaPlaylist *backgroundPlaylist;
    QLabel *title;


private slots:
    void slotDeletePassive(QGraphicsItem * item);
    void slotCreatePassive();
    void slotUpdateAll();
    void slotGameOver();
   // void slotCreateEnemy();
    void slotCreatePowerup();
    void slotChangeSpeedPlayer();
    void slotChangeSpeedEnemy();

    void on_pushButton_clicked();

public:
    int size_x=600;
    int size_y=500;
};


class Settings{
public:
    static int speed_player;
    static int speed_enemy;

    //static int required_space;
    //static int start;
};

#endif // WIDGET_H
