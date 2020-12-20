#include "widget.h"
#include "ui_widget.h"
#include <QStyle>
#include <QTime>

int Settings::speed_player=4;
int Settings::speed_enemy=2;

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);
    this->setFixedSize(1300,1050);
    this->setGeometry(QStyle::alignedRect(
                          Qt::LeftToRight,
                          Qt::AlignCenter,
                          this->size(),
                          qApp->desktop()->availableGeometry()));
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setSceneRect(-size_x,-size_y,2*size_x,2*size_y);

    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));

    QImage back;
    back.load(":/background.png");
    scene->setBackgroundBrush(back);

    int id = QFontDatabase::addApplicationFont(":/font.otf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont ft_score(family);

    totalScore=0;
    totalScoreLabel = new QLabel(this);
    totalScoreLabel->setText("Ваш счет: "+QString::number(totalScore));
    totalScoreLabel->setStyleSheet("QLabel { font-size: 32px; color: red}");
    totalScoreLabel->setGeometry(850, 70, 250, 70);
    totalScoreLabel->setFont(ft_score);
    title = new QLabel(this);
    title->setStyleSheet("QLabel { font-size: 64px; color: red}");
    title->setAlignment(Qt::AlignCenter);
    title->setFont(ft_score);
    title->setText("Павел Сергеевич\n против\n должников");
    title->setGeometry(300, 200, 700, 300);


}

void Widget::AddGrass(){
    while (grassList.size()<MAXGRASS){
        grassBackground *grass = new grassBackground();
        scene->addItem(grass);
        grass->setPos((qrand() % (size_x+1)) * ((qrand()%2 == 1)?1:-1),
                      (qrand() % (size_y+1)) * ((qrand()%2 == 1)?1:-1));
        grass->setZValue(-3);
        grassList.append(grass);
    }
}

Widget::~Widget() { delete ui; }

void Widget::slotChangeSpeedPlayer(){
    timerPowerupLastingPizza->stop();
    Settings::speed_player=4;

}

void Widget::slotChangeSpeedEnemy(){
    timerPowerupLastingCroissant->stop();
    Settings::speed_enemy=2;
}

void Widget::slotCreatePowerup(){
    if (powerupPizzaList.size()+powerupCroissantList.size() < MAX/3) {
        switch (qrand()%2+1) {
        case 1:{
            PowerupPizza *pow = new PowerupPizza();
            scene->addItem(pow);
            pow->setPos((qrand() % (size_x+1)) * ((qrand()%2 == 1)?1:-1),
                          (qrand() % (size_y+1)) * ((qrand()%2 == 1)?1:-1));
            pow->setZValue(-2);
            //qDebug()<<passiveList<<" coffee "<<pas->pos();
            powerupPizzaList.append(pow);}
            break;
        case 2:{
            PowerupCroissant *cro = new PowerupCroissant();
            scene->addItem(cro);
            cro->setPos((qrand() % (size_x+1)) * ((qrand()%2 == 1)?1:-1),
                          (qrand() % (size_y+1)) * ((qrand()%2 == 1)?1:-1));
            cro->setZValue(-2);
            //qDebug()<<passiveList<<" coffee "<<pas->pos();
            powerupCroissantList.append(cro);}
            break;
        }
    }
}

void Widget::slotDeletePassive(QGraphicsItem *item) {
    foreach (QGraphicsItem *poc, powerupCroissantList) {
           if (poc == item) {
               timerPowerupLastingCroissant->start(2000);
               scene->removeItem(poc);
               powerupCroissantList.removeOne(poc);
               delete poc;
               totalScore++;
               QMediaPlayer * m_player = new QMediaPlayer(this);
               QMediaPlaylist * m_playlist = new QMediaPlaylist(m_player);
               m_player->setPlaylist(m_playlist);
               m_playlist->addMedia(QUrl("qrc:/food.mp3"));
               m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
               m_player->play();
           }
    }
    foreach (QGraphicsItem *pow, powerupPizzaList) {
           if (pow == item) {
               timerPowerupLastingPizza->start(2000);
               scene->removeItem(pow);
               powerupPizzaList.removeOne(pow);
               delete pow;
               totalScore++;
               QMediaPlayer * m_player = new QMediaPlayer(this);
               QMediaPlaylist * m_playlist = new QMediaPlaylist(m_player);
               m_player->setPlaylist(m_playlist);
               m_playlist->addMedia(QUrl("qrc:/food.mp3"));
               m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
               m_player->play();
           }
    }
 foreach (QGraphicsItem *pas, passiveList) {
        if (pas == item) {
            scene->removeItem(pas);
            passiveList.removeOne(pas);
            delete pas;
            totalScore++;
            QMediaPlayer * m_player = new QMediaPlayer(this);
            QMediaPlaylist * m_playlist = new QMediaPlaylist(m_player);
            m_player->setPlaylist(m_playlist);
            m_playlist->addMedia(QUrl("qrc:/food.mp3"));
            m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
            m_player->play();
        }
    }
    CreateEnemy();
}

void Widget::slotCreatePassive() {
    if (passiveList.size() < MAX) {
    Passive *pas = new Passive();
    scene->addItem(pas);
    pas->setPos((qrand() % (size_x+1)) * ((qrand()%2 == 1)?1:-1),
                  (qrand() % (size_y+1)) * ((qrand()%2 == 1)?1:-1));
    pas->setZValue(-2);
    //qDebug()<<passiveList<<" coffee "<<pas->pos();
    passiveList.append(pas);}
    //qDebug()<<passiveList.size();
}

void Widget::CreateEnemy() {
    if (enemyPosition<3){
        switch (enemyPosition) {
        case 1:
            enemy1 = new Enemy(player);
            scene->addItem(enemy1);
            enemy1->setPos(size_x,size_y);
            enemyPosition++;
            connect(enemy1, &Enemy::signalCheckGameOver, this, &Widget::slotGameOver);
            break;
        case 2:
            if (totalScore>9){
                enemy2 = new Enemy(player);
                scene->addItem(enemy2);
                enemy2->setPos(-size_x,-size_y);
                enemyPosition++;
                connect(enemy2, &Enemy::signalCheckGameOver, this, &Widget::slotGameOver);
                break;
            }
        }
    }
}
/*
void Widget::slotCreateEnemy() {



    if (enemyPosition<3){
        switch (enemyPosition) {
        case 1:
            enemy1 = new Enemy(player);
            scene->addItem(enemy1);
            enemy1->setPos(size_x,size_y);
            enemyPosition++;
            connect(enemy1, &Enemy::signalCheckGameOver, this, &Widget::slotGameOver);
            break;
        case 2:
            enemy2 = new Enemy(player);
            scene->addItem(enemy2);
            enemy2->setPos(-size_x,-size_y);
            enemyPosition++;
            connect(enemy2, &Enemy::signalCheckGameOver, this, &Widget::slotGameOver);
            break;
        }
    }

    if (enemyList.size() < MAXENEMY) {
    Enemy *enemy = new Enemy(player);
    scene->addItem(enemy);
    switch (enemyPosition) {
    case 1:
        enemy->setPos(size_x,size_y);
        enemyPosition++;
        break;
    case 2:
        enemy->setPos(size_x,-size_y);
        enemyPosition++;
        break;
    case 3:
        enemy->setPos(-size_x,size_y);
        enemyPosition++;
        break;
    case 4:
        enemy->setPos(-size_x,-size_y);
        enemyPosition=1;
        break;
    }
    enemy->setZValue(-1);
    //enemy->setPos(250,250); //Так как игровые координаты от (-250,-250) до (250,250)
    //enemy->setZValue(-1);
    connect(enemy, &Enemy::signalCheckGameOver, this, &Widget::slotGameOver);

    enemyListObj.push_back(enemy);
    enemyList.append(enemy);}
    //qDebug()<<enemyList.size();
}*/

void Widget::slotUpdateAll(){
    scene->update();
    totalScoreLabel->setText("Ваш счет: "+QString::number(totalScore));
}

void Widget::slotGameOver() {
    backgroundPlayer->stop();
    QMediaPlayer * m_player = new QMediaPlayer(this);
    QMediaPlaylist * m_playlist = new QMediaPlaylist(m_player);
    m_player->setPlaylist(m_playlist);
    m_playlist->addMedia(QUrl("qrc:/death.mp3"));
    m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    m_player->play();
    disconnect(timerCreatePassive, &QTimer::timeout, this, &Widget::slotCreatePassive);
   // disconnect(timerCreateEnemy, &QTimer::timeout, this, &Widget::slotCreateEnemy);
    disconnect(player, &Player::signalCheckItem, this, &Widget::slotDeletePassive);
    disconnect(timerPowerup, &QTimer::timeout, this, &Widget::slotCreatePowerup);
    player->deleteLater();

    disconnect(enemy1, &Enemy::signalCheckGameOver, this, &Widget::slotGameOver);
    enemy1->deleteLater();
    if (enemyPosition>2){
        disconnect(enemy2, &Enemy::signalCheckGameOver, this, &Widget::slotGameOver);
        //scene->removeItem(enemy2);
        enemy2->deleteLater();
    }
   // scene->removeItem(player);

    foreach (QGraphicsItem *pas, passiveList) {
        scene->removeItem(pas);
        passiveList.removeOne(pas);
        delete pas;
    }
    foreach (QGraphicsItem *paw, powerupPizzaList) {
        scene->removeItem(paw);
        powerupPizzaList.removeOne(paw);
        delete paw;
    }
    foreach (QGraphicsItem *pax, powerupCroissantList) {
            scene->removeItem(pax);
            powerupCroissantList.removeOne(pax);
            delete pax;
        }
    foreach (QGraphicsItem *grass, grassList) {
        scene->removeItem(grass);
        grassList.removeOne(grass);
        delete grass;
    }
    Settings::speed_enemy=2;
    Settings::speed_player=4;
    gamestate=0;
    QMessageBox::warning(this,
                         "Вас догнали студенты",
                         "Игра окончена. Вам удалось набрать "+QString::number(totalScore)+" очков");
    totalScore=0;
    title->setText("Павел Сергеевич\n против\n должников");
   /* foreach (Enemy *enemy, enemyListObj){
        disconnect(enemy, &Enemy::signalCheckGameOver, this, &Widget::slotGameOver);
        enemy->deleteLater();
    }
    foreach (QGraphicsItem *enemy, enemyList) {
        scene->removeItem(enemy);
        passiveList.removeOne(enemy);
        delete enemy;
    }*/
}

void Widget::on_pushButton_clicked()
{
    if (gamestate==0){
        title->setText("   ");
        backgroundPlayer = new QMediaPlayer(this);
        backgroundPlaylist = new QMediaPlaylist(backgroundPlayer);
        backgroundPlayer->setPlaylist(backgroundPlaylist);
        backgroundPlaylist->addMedia(QUrl("qrc:/soundtrack.mp3"));
        backgroundPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
        backgroundPlayer->setVolume(70);
        backgroundPlayer->play();

        timerCreatePassive = new QTimer();
        connect(timerCreatePassive, &QTimer::timeout, this, &Widget::slotCreatePassive);
        timerCreatePassive->start(1000);

        timerUpdate= new QTimer();
        connect(timerUpdate, &QTimer::timeout, this, &Widget::slotUpdateAll);
        timerUpdate->start(10);

        player= new Player();
        scene->addItem(player);
        player->setPos(0,0);
        timerMovement = new QTimer();
        connect(timerMovement, &QTimer::timeout, player, &Player::slotMovement);
        timerMovement->start(20);
        connect(player, &Player::signalCheckItem, this, &Widget::slotDeletePassive);

       // timerCreateEnemy = new QTimer();
       // connect(timerCreateEnemy, &QTimer::timeout, this, &Widget::slotCreateEnemy);
       // timerCreateEnemy->start(2000);
        enemyPosition=1;

        timerPowerup= new QTimer();
        connect(timerPowerup, &QTimer::timeout, this, &Widget::slotCreatePowerup);
        timerPowerup->start(2000);

        timerPowerupLastingPizza= new QTimer();
        connect(timerPowerupLastingPizza, &QTimer::timeout, this, &Widget::slotChangeSpeedPlayer);
        timerPowerupLastingCroissant= new QTimer();
        connect(timerPowerupLastingCroissant, &QTimer::timeout, this, &Widget::slotChangeSpeedEnemy);
        AddGrass();
        gamestate=1;
    }

}
