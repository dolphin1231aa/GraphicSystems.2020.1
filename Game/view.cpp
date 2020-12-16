#include "view.h"
#include <windows.h>

#include <QPushButton>
#include <QApplication>

View::View(QWidget *parent)
    : QGraphicsView(parent) {

    scene = new QGraphicsScene();
    this->setScene(scene);

    this->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOff);

    this->setFixedSize(800,600);
    this->setRenderHint(QPainter::Antialiasing);

    QImage background;
    background.load(":/img/background.png");
    timer_game = new QTimer();
    timer_move = new QTimer();
    qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
    scene->setBackgroundBrush(background);

    /* Счет */

    lbl_coffee = new QLabel(this);
    lbl_croissant = new QLabel(this);
    lbl_croissant_score = new QLabel(this);
    lbl_coffee_score = new QLabel(this);

    coffee_img = new QPixmap(":/img/coffee.png");
    croissant_img = new QPixmap(":/img/croissant.png");
    platform_img = new QPixmap(":/img/platform.png");

    lbl_coffee->setPixmap(*coffee_img);
    lbl_croissant->setPixmap(QPixmap(":/img/croissant.png"));

    lbl_coffee->setGeometry(700, 10, coffee_img->width(), coffee_img->height());
    lbl_croissant->setGeometry(689, 95, croissant_img->width(), croissant_img->height());

    int id = QFontDatabase::addApplicationFont(":/fonts/score.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont ft_score(family);

    lbl_coffee_score->setText(QString::number(coffee_score));
    lbl_coffee_score->setStyleSheet("QLabel { font-size: 32px;}");
    lbl_coffee_score->setFont(ft_score);
    lbl_coffee_score->setGeometry(764, 10, coffee_img->width(), coffee_img->height());

    lbl_croissant_score->setText(QString::number(croissant_score));
    lbl_croissant_score->setStyleSheet("QLabel { font-size: 32px;}");
    lbl_croissant_score->setFont(ft_score);
    lbl_croissant_score->setGeometry(764, 90, croissant_img->width(), croissant_img->height());

    /* Комбинация */

    lbl_title = new QLabel(this);
    lbl_title->setStyleSheet("QLabel { font-size: 32px; color: white; }");
    lbl_title->setFont(ft_score);

    /* Для затемнения */

    frame = new QFrame(this);
    frame->resize(800,600);

    /* Звуки */

    m_sounds = new QMediaPlayer(this);
    m_music = new QMediaPlayer(this);

    m_playlist_croissant = new QMediaPlaylist(m_sounds);
    m_playlist_death = new QMediaPlaylist(m_sounds);
    m_playlist_background = new QMediaPlaylist(m_music);

    m_music->setPlaylist(m_playlist_background);

    m_playlist_background->addMedia(QUrl("qrc:/sound/background_music.mp3"));

    m_music->setVolume(10);
    m_playlist_background->setPlaybackMode(QMediaPlaylist::Loop);

    QDir dir(":/sound/croissant/");
    QStringList filter;
    filter<< QLatin1String("*.mp3") << QLatin1String("*.wav");
    dir.setNameFilters(filter);
    QFileInfoList filelistinfo = dir.entryInfoList();

    foreach (const QFileInfo &fileinfo, filelistinfo) {
        m_playlist_croissant->addMedia(QUrl("qrc:/sound/croissant/" + fileinfo.fileName()));
    }

    m_playlist_death->addMedia(QUrl("qrc:/sound/death/bang.mp3"));
    m_playlist_death->addMedia(QUrl("qrc:/sound/death/funeral.mp3"));
    m_playlist_death->addMedia(QUrl("qrc:/sound/death/win.mp3"));


    itm_positionY = {0, -50, -140, -300};
    coffee_img = new QPixmap(":/img/coffee1.png");
    gameStart();
}

void View::gameStart() {
    frame->hide();

    player = new Player();
    scene->addItem(player->getSprite());

    connect(timer_game, &QTimer::timeout, this, &View::gameTimer);
    timer_game->start(15);

    connect(timer_move, &QTimer::timeout, this, &View::gameMove);
    timer_move->start(80);

    x = 0;
    coffee_combination = 2 * (qrand() % (coffeeMax/4 - 1) + 1);
    croissant_combination = coffee_combination/2 * 3;

    lbl_title->setText("Your lucky combination: " + QString::number(coffee_combination) + " " +  QString::number(croissant_combination));

    m_music->play();

    lbl_title->show();
    lbl_coffee->show();
    lbl_croissant->show();
    lbl_coffee_score->show();
    lbl_croissant_score->show();

    lbl_coffee_score->setText(QString::number(coffee_score));
    lbl_croissant_score->setText(QString::number(croissant_score));
    createPlatform();
    createCoffee();
    createCroissant();

    scene->setSceneRect(minX, -600, maxX, 600);
    this->setSceneRect(0, -600, 800, 600);
}

void View::gameMove() {
    if (GetAsyncKeyState(65) || GetAsyncKeyState(68) || GetAsyncKeyState(VK_SPACE)) {
        if(GetAsyncKeyState(65)) { // клавиша A
            if (x > minX) {
                if (player->getPosition().x() >= this->width()/3 - player->getWidth()/4 && player->getPosition().x() <= maxX - this->width()/2) {
                    setFrame();
                }
                player->setSpeed(-abs(player->getSpeed()));
                x += player->getSpeed();
                player->move_horizontal();
            }
        }
        if(GetAsyncKeyState(68) ) { // клавиша D
            if (x <= maxX) {
                if (player->getPosition().x() >= this->width()/2 && player->getPosition().x() <= maxX - this->width()/3) {
                    setFrame();
                }
                player->setSpeed(abs(player->getSpeed()));
                x += player->getSpeed();
                player->move_horizontal();
            }
        }
        if(GetAsyncKeyState(VK_SPACE) ) {
            player->move_vertical();
        }
    }

    QList<QGraphicsItem *> foundItemsRight = scene->items(QRect(player->getPosition().x(), 0, 400, -600));
    QList<QGraphicsItem *> foundItemsLeft = scene->items(QRect(player->getPosition().x() - 400, 0, 400, -600));

    foreach (auto *croissan, croissants) {
        croissan->getTimer()->stop();
        foreach (QGraphicsItem *item, foundItemsRight) {
            if (item == player->getSprite()) continue;
            if (item == croissan->getSprite() &&  croissan->getSprite()->x() <= maxX) {
                croissan->setSpeed(abs(croissan->getSpeed()));
                croissan->getTimer()->start(80);
            }
        }

        foreach (QGraphicsItem *item, foundItemsLeft) {
            if (item == player->getSprite()) continue;
            if (item == croissan->getSprite() &&  croissan->getSprite()->x() >= minX) {
                croissan->setSpeed(-abs(croissan->getSpeed()));
                croissan->getTimer()->start(80);
            }
        }
        if (!croissan->getTimer()->isActive()) croissan->step();

    }
}


void View::gameTimer() {

    QList<QGraphicsItem *> foundItemsClose = scene->items(QRect(player->getPosition().x(),
                                                                player->getPosition().y() - player->getHeight(),
                                                                player->getWidth(),
                                                                player->getHeight()));

    foreach (QGraphicsItem *item, foundItemsClose) {
        if (item == player->getSprite()) continue;
        deleteItem(item);
    }

    QList<QGraphicsItem *> foundPlatformAhead = scene->items(QRect(player->getPosition().x(),
                                                                   player->getPosition().y(),
                                                                   player->getWidth()/1.5,
                                                                   platform_img->height()/2));


    QList<QGraphicsItem *> foundPlatformBehind = scene->items(QRect(player->getPosition().x() + player->getWidth()/1.5 ,
                                                                    player->getPosition().y(),
                                                                    player->getWidth() - player->getWidth()/1.5,
                                                                    platform_img->height()/2));

    if (player->getSpeed() > 0) findPlatform(foundPlatformAhead, foundPlatformBehind);
    if (player->getSpeed() < 0) findPlatform(foundPlatformBehind, foundPlatformAhead);

    if (foundPlatformAhead.size() == 0 && foundPlatformBehind.size() == 0 && player->getPosition().y() != 0 && y != 0
            &&  (player->getPositionVertical() == 0 || player->getPositionVertical() == -1)) {

        player->setGroundY(y = 0);
        player->setPositionVertical(-1);
        player->move_vertical();


    }

    if (croissant_score > croissant_combination) gameOver(-1);
    if (coffee_score > coffee_combination) gameOver(0);
    if (croissant_score == croissant_combination && coffee_score == coffee_combination) gameOver(1);
}

void View::createCoffee() {
    for (int i = 0; i < coffeeMax; i++) {
        StaticObject *coffee = new StaticObject(coffee_img);
        QPoint position = randomPos(coffee_img->width(), coffee_img->height() + platform_img->height(), 1);
        coffee->setPos(position.x(), position.y()  - coffee_img->height());
        scene->addItem(coffee);
        coffee_list.append(coffee);
    }
}

void View::createCroissant() {
    for (int i = 0; i < croissantMax; i++) {
        QPoint position = randomPos(croissant_img->width(), croissant_img->height(), 0);
        Croissant* croissant = new Croissant(position.x(), position.y(), randomSpeed());
        scene->addItem(croissant->getSprite());
        croissant_list.append(croissant->getSprite());
        croissants.append(croissant);
    }

}

void View::createPlatform() {
    for (int i = 0; i < platformMax; i++) {

        StaticObject *platform = new StaticObject(platform_img);

        int randX = (qrand() % (maxX-600) )+ 600;
        int randY = itm_positionY[qrand() % 2 + 2];

        QList<QGraphicsItem *> items = scene->items(QRect(randX,  randY, platform_img->width(), platform_img->height()));

        while (items.size() != 0) {
            randX = (qrand() % (maxX - 600) )+ 600;
            randY = itm_positionY[qrand() % 2 + 2];
            items = scene->items(QRect(randX,  randY, platform_img->width(), platform_img->height()));
        }

        platform->setPos(randX, randY);
        platform->setZValue(-1);
        scene->addItem(platform);
        platform_list.append(platform);
    }
}

void View::findPlatform(QList<QGraphicsItem *> foundPlatformAhead, QList<QGraphicsItem *> foundPlatformBehind) {
    foreach (QGraphicsItem *item, foundPlatformAhead) {

        for (int i = 0; i < platform_list.size(); i++) {

            if (item == player->getSprite()) continue;

            if (item == platform_list.at(i) && foundPlatformBehind.size() != 0) {

                if (player->getPositionVertical() == -1)
                    player->setGroundY(y = platform_list.at(i)->y());
            }

            if (item == platform_list.at(i) && foundPlatformBehind.size() == 0) {

                player->setGroundY(y = 0);
                player->setPositionVertical(-1);
                player->move_vertical();
            }
        }
    }
}


void View::gameOver(char key) {
    m_music->stop();
    deleteAllItem(coffee_list);
    deleteAllItem(platform_list);

    disconnect(timer_move, &QTimer::timeout, this, &View::gameMove);
    disconnect(timer_game, &QTimer::timeout, this, &View::gameTimer);

    foreach (QGraphicsItem *itm, croissant_list) {

        scene->removeItem(itm);
        croissant_list.removeOne(itm);

        foreach (auto *croissan, croissants) {

            if (itm == croissan->getSprite()) {
                croissan->getTimer()->stop();
                croissants.removeOne(croissan);
                croissan->deleteLater();
            }
        }

        delete itm;
    }

    player->deleteLater();
    scene->removeItem(player->getSprite());

    croissant_score = 0;
    coffee_score = 0;

    int id = QFontDatabase::addApplicationFont(":/fonts/score.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont ft_score(family);

    QString text;
    QPixmap icon;

    lbl_title->hide();
    lbl_coffee->hide();
    lbl_croissant->hide();
    lbl_coffee_score->hide();
    lbl_croissant_score->hide();

    m_sounds->setPlaylist(m_playlist_death);
    switch (key) {
    case -1: {
        text = "Сегодня не ваш день. Круассанов оказалось слишком много и вы... лопнули";
        frame->setStyleSheet("QFrame {background-color: rgba(0, 0, 0, 70%);  background-image: url(:/img/croissant.png);}");
        icon = QPixmap(":/icon/bang.png");
        m_playlist_death->setCurrentIndex(0);
        break;
    }
    case 0: {
        text = "Сожалеем, но вы погибли от передозировки кофеина";
        frame->setStyleSheet("QFrame {background-color: rgba(0, 0, 0, 70%);  background-image: url(:/img/coffee.png);}");
        icon = QPixmap(":/icon/pepe.png");
        m_playlist_death->setCurrentIndex(1);
        break;
    }
    case 1: {
        text = "Поздравляем! Была собрана божественная комбинация!";
        frame->setStyleSheet("QFrame {background-image: url(:/img/clover.png);}");
        icon = QPixmap(":/icon/chick.png");
        m_playlist_death->setCurrentIndex(2);
        break;
    }
    }

    frame->show();

    m_playlist_death->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    m_sounds->play();

    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox { font-size: 20px; }");
    msgBox.setText(text + "\n\nХотите начать заново?");
    msgBox.setWindowFlag(Qt::FramelessWindowHint);
    msgBox.addButton(tr("Да!"), QMessageBox::YesRole);
    msgBox.addButton(tr("На сегодня достаточно.."), QMessageBox::NoRole);

    msgBox.setFont(ft_score);
    msgBox.setIconPixmap(icon);
    bool answer = msgBox.exec();

    if (answer) {
        qApp->quit(); // Спросить
    } else {
        m_sounds->stop();
        gameStart();
    }

}


void View::deleteAllItem(QList<QGraphicsItem *> &items) {
    foreach (QGraphicsItem *itm, items) {
        scene->removeItem(itm);
        items.removeOne(itm);
        delete itm;
    }
}

QPoint View::randomPos(unsigned int width, unsigned int height, int randY) {
    int randX = (qrand() % (maxX-600)) + 600;
    randY == 1 ? randY = itm_positionY[qrand() % 3 + 1] : randY = itm_positionY[0];

    QList<QGraphicsItem *> items = scene->items(QRect(randX  - 40,  randY - height, width + 80, height/3));
    QList<QGraphicsItem *> itemsPlatform = scene->items(QRect(randX + width/3, randY, width - width/2, platform_img->height()/4));

    while (items.size() != 0 || (randY != itm_positionY[1] && randY != itm_positionY[0] && itemsPlatform.size() == 0)) {

        randX = (qrand() % (maxX - 600) )+ 600;
        if (randY != itm_positionY[0]) randY = itm_positionY[qrand() % 3 + 1];
        items = scene->items(QRect(randX  - 40,  randY - height, width + 80, height/3));
        itemsPlatform = scene->items(QRect(randX + width/3, randY, width - width/2, platform_img->height()/4));
    }
    return QPoint(randX, randY);
}


unsigned char View::randomSpeed() {
    int speed = qrand() % 15 + 5;
    return speed;
}

void View::setFrame() {
    QPoint player_pos = player->getPosition();
    QRect player_rect(QPoint(player_pos.x() - this->width()/2, 0), QPoint(player_pos.x() + this->width() - this->width()/3,  -this->height()));
    this->setSceneRect(player_rect);
}

void View::deleteItem (QGraphicsItem *item) {
    foreach (QGraphicsItem *itm, coffee_list) {
        if (itm == item) {
            scene->removeItem(itm);
            coffee_list.removeOne(itm);
            delete itm;
            lbl_coffee_score->setText(QString::number(++coffee_score));
            scene->update();
        }
    }

    foreach (QGraphicsItem *itm, croissant_list) {
        if (itm == item) {
            scene->removeItem(itm);
            croissant_list.removeOne(itm);
            foreach (auto *croissan, croissants) {
                if (itm == croissan->getSprite()) {
                    croissan->getTimer()->stop();
                    croissants.removeOne(croissan);
                    croissan->deleteLater();
                    m_sounds->setPlaylist(m_playlist_croissant);
                    lbl_croissant_score->setText(QString::number(++croissant_score));
                    m_playlist_croissant->setCurrentIndex(qrand() % 6);
                    m_playlist_croissant->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
                    m_sounds->play();
                    scene->update();
                }
            }
            delete itm;
        }
    }
}


View::~View() {}
