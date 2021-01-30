#include "triangle.h"

Triangle::Triangle(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    angle = 0;      /// Задаём угол поворота графического объекта
    steps = 1;      /// Задаём стартовое положение ножек божьей коровки
    countForSteps = 0;      /// Счётчик для отсчета тиков таймера, при которых мы нажимали на кнопки
    setRotation(angle);     /// Устанавливаем угол поворота графического объекта

    m_player = new QMediaPlayer(this);          // Инициализация плеера
    m_playlist = new QMediaPlaylist(m_player);  // Инициализация плейлиста

    m_player->setPlaylist(m_playlist);          // Установка плейлиста в аудио плеер
    m_playlist->addMedia(QUrl("qrc:/game/1.mp3"));       // Добавление трека в плейлист
    m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop); // Зацикливание трека
}

Triangle::~Triangle()
{

}

QRectF Triangle::boundingRect() const
{
    return QRectF(-40,-50,80,100);   /// Ограничиваем область, в которой лежит божья коровка
}

void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Рисуем ножки
    painter->setPen(QPen(Qt::black, 2));
    if(steps == 0){     // Первое положение ножек
        // Left 1
        painter->drawLine(-24,-37,-22,-25);
        painter->drawLine(-22,-25,-17,-15);
        painter->drawLine(-17,-15,-10,-5);
        // Right 1
        painter->drawLine(37,-28,28,-18);
        painter->drawLine(28,-18,24,-8);
        painter->drawLine(24,-8,10,-5);

        // Left 2
        painter->drawLine(-35,-20,-25,-11);
        painter->drawLine(-25,-11,-14,-5);
        painter->drawLine(-14,-5,0,5);
        // Right 2
        painter->drawLine(37,-12,32,-4);
        painter->drawLine(32,-4,24,2);
        painter->drawLine(24,2,0,5);

        // Left 3
        painter->drawLine(-35,35,-26,24);
        painter->drawLine(-26,24,-16,16);
        painter->drawLine(-16,16,0,0);
        // Right 3
        painter->drawLine(37,26,32,17);
        painter->drawLine(32,17,24,8);
        painter->drawLine(24,8,0,0);
    } else if (steps == 1){     // Второе положение ножек
        // Left 1
        painter->drawLine(-32,-32,-25,-22);
        painter->drawLine(-25,-22,-20,-12);
        painter->drawLine(-20,-12,-10,-5);
        // Right 1
        painter->drawLine(32,-32,25,-22);
        painter->drawLine(25,-22,20,-12);
        painter->drawLine(20,-12,10,-5);

        // Left 2
        painter->drawLine(-39,-15,-30,-8);
        painter->drawLine(-30,-8,-18,-2);
        painter->drawLine(-18,-2,0,5);
        // Right 2
        painter->drawLine(39,-15,30,-8);
        painter->drawLine(30,-8,18,-2);
        painter->drawLine(18,-2,0,5);

        // Left 3
        painter->drawLine(-39,30,-30,20);
        painter->drawLine(-30,20,-20,12);
        painter->drawLine(-20,12,0,0);
        // Right 3
        painter->drawLine(39,30,30,20);
        painter->drawLine(30,20,20,12);
        painter->drawLine(20,12,0,0);
    } else if (steps == 2){     // Третье положение ножек
        // Left 1
        painter->drawLine(-37,-28,-28,-18);
        painter->drawLine(-28,-18,-24,-8);
        painter->drawLine(-24,-8,-10,-5);
        // Right 1
        painter->drawLine(24,-37,22,-25);
        painter->drawLine(22,-25,17,-15);
        painter->drawLine(17,-15,10,-5);

        // Left 2
        painter->drawLine(-37,-12,-32,-4);
        painter->drawLine(-32,-4,-24,2);
        painter->drawLine(-24,2,0,5);
        // Right 2
        painter->drawLine(35,-20,25,-11);
        painter->drawLine(25,-11,14,-5);
        painter->drawLine(14,-5,0,5);

        // Left 3
        painter->drawLine(-37,26,-32,17);
        painter->drawLine(-32,17,-24,8);
        painter->drawLine(-24,8,0,0);
        // Right 3
        painter->drawLine(35,35,26,24);
        painter->drawLine(26,24,16,16);
        painter->drawLine(16,16,0,0);
    }

    // Тело
    painter->setBrush(Qt::red);
    painter->drawEllipse(-25, -20,50, 60);
    painter->setBrush(Qt::red);
    painter->drawEllipse(-20,-20,40,25);
    painter->setBrush(Qt::black);
    painter->drawLine(0,38,0,0);
    painter->drawEllipse(5,20,10,10);
    painter->drawEllipse(13,5,5,5);
    painter->drawEllipse(-6,0,13,13);
    painter->drawEllipse(-20,0,5,5);
    painter->drawEllipse(-16,17,10,10);


    // Глаза
    // Если в близости от божьей коровки есть объект, то глаза божьей коровки желтеют
    painter->setBrush(scene()->collidingItems(this).isEmpty() ? Qt::white : Qt::yellow);
    // painter->setBrush(Qt::green);
    painter->drawEllipse(-15, -15, 12, 15);
    painter->drawEllipse(3, -15, 12, 15);


    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Triangle::slotGameTimer()
{
    /* Проверяем, нажата ли была какая-либо из кнопок управления объектом.
     * Прежде чем считать шажки
     * */
    if(GetAsyncKeyState(VK_LEFT) ||
       GetAsyncKeyState(VK_RIGHT) ||
       GetAsyncKeyState(VK_UP) ||
       GetAsyncKeyState(VK_DOWN))
    {
        /* Поочерёдно выполняем проверку на нажатие клавиш
         * с помощью функции асинхронного получения состояния клавиш,
         * которая предоставляется WinAPI
         * */
        if(GetAsyncKeyState(VK_LEFT)){
            angle -= 5;        // Задаём поворот на 5 градусов влево
            setRotation(angle); // Поворачиваем объект
        }
        if(GetAsyncKeyState(VK_RIGHT)){
            angle += 5;        // Задаём поворот на 5 градусов вправо
            setRotation(angle); // Поворачиваем объект
        }
        if(GetAsyncKeyState(VK_UP)){
            setPos(mapToParent(0, -2));     /* Продвигаем объект на 5 пискселей вперёд
                                             * перетранслировав их в координатную систему
                                             * графической сцены
                                             * */
        }
        if(GetAsyncKeyState(VK_DOWN)){
            setPos(mapToParent(0, 2));      /* Продвигаем объект на 5 пискселей назад
                                             * перетранслировав их в координатную систему
                                             * графической сцены
                                             * */
        }


        countForSteps++;
        if(countForSteps == 6){
            steps = 2;
            update(QRectF(-40,-50,80,100));
        } else if (countForSteps == 12){
            steps = 1;
            update(QRectF(-40,-50,80,100));
        } else if (countForSteps == 18){
            steps = 0;
            update(QRectF(-40,-50,80,100));
        } else if (countForSteps == 24) {
            steps = 1;
            update(QRectF(-40,-50,80,100));
            countForSteps = 0;
        }

        m_player->play();   // Плеер играет только тогда, когда божья коровка движется
    } else {
        m_player->stop();   // Если божья коровка не движется, то отключаем плеер
    }

    /* Производим проверку на то, наткнулась ли божья коровка на какой-нибудь
     * элемент на графической сцене.
     * Для этого определяем небольшую область перед божьей коровкой,
     * в которой будем искать элементы
     * */
    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                           << mapToScene(0, 0)
                                                           << mapToScene(-20, -20)
                                                           << mapToScene(20, -20));
    /* После чего проверяем все элементы.
     * Один из них будет сама божья коровка - с ней ничего не делаем.
     * А с остальными высылаем сигнал в ядро игры
     * */
    foreach (QGraphicsItem *item, foundItems) {
        if (item == this)
            continue;
        emit signalCheckItem(item);
    }

    /** Проверка выхода за границы поля
     * Если объект выходит за заданные границы, то возвращаем его назад
     * */
    if(this->x() - 10 < -250){
        this->setX(-240);       // слева
    }
    if(this->x() + 10 > 250){
        this->setX(240);        // справа
    }

    if(this->y() - 10 < -250){
        this->setY(-240);       // сверху
    }
    if(this->y() + 10 > 250){
        this->setY(240);        // снизу
    }
}
