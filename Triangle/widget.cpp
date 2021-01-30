#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(600,640);/// Задаем размеры виджета, то есть окна

    this->setFixedSize(600,640);    /// Фиксируем размеры виджета

    scene = new QGraphicsScene();   /// Инициализируем графическую сцену

    ui->graphicsView->setScene(scene);  /// Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по горизонтали
ui->graphicsView->setBackgroundBrush(Qt::green);
    scene->setSceneRect(-250,-250,500,500); /// Устанавливаем область графической сцены


    timer = new QTimer();
    timerCreateApple = new QTimer();

    gameState = GAME_STOPED;

    pauseKey = new QShortcut(this);
    pauseKey->setKey(Qt::Key_Pause);
    connect(pauseKey, &QShortcut::activated, this, &Widget::slotPause);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotDeleteApple(QGraphicsItem *item)
{
    /* Получив сигнал от божьей коровки
     * Перебираем весь список яблок и удаляем найденное яблоко
     * */
    foreach (QGraphicsItem *apple, apples) {
        if(apple == item){
            scene->removeItem(apple);   // Удаляем со сцены
            apples.removeOne(apple);    // Удаляем из списка
            delete apple;               // Вообще удаляем
            ui->lcdNumber->display(count++);    /* Увеличиваем счёт на единицу
                                                 * и отображаем на дисплее
                                                 * */
            // Звук поедания яблока
            QMediaPlayer * m_player = new QMediaPlayer(this);   // Инициализируем плеер
            QMediaPlaylist * m_playlist = new QMediaPlaylist(m_player); // Создаём плейлист

            m_player->setPlaylist(m_playlist);  // Устанавливаем плейлист в плеер
            m_playlist->addMedia(QUrl("qrc:/game/3.wav")); // Добавляем аудио в плеер
            m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce); // Проигрывам один раз
            m_player->play();   // Запускаем плеер
        }
    }
}

void Widget::slotCreateApple()
{
    Apple *apple = new Apple(); // Создаём яблоко
    scene->addItem(apple);      // Помещаем его в сцену со случайной позицией
    apple->setPos((qrand() % (251)) * ((qrand()%2 == 1)?1:-1),
                  (qrand() % (251)) * ((qrand()%2 == 1)?1:-1));
    apple->setZValue(-1);       /* Помещаем яблоко ниже божьей коровки, то есть божья коровка
                                 * на сцене будет выше яблок
                                 * */
    apples.append(apple);       // Добавляем  Список
}

void Widget::on_pushButton_clicked()
{
    count = 0;
    ui->lcdNumber->display(count);
    triangle = new Triangle();      /// Инициализируем божью коровку

    scene->addItem(triangle);       /// Добавляем на сцену божью коровку
    triangle->setPos(0,0);          /// Устанавливаем божью коровку в центр сцены

    spider = new Spider(triangle);  // Инициализируем паука
    scene->addItem(spider);         // Добавляем паука на сцену
    spider->setPos(180,180);        // Устанавливаем позицию паука

    /* Подключаем сигнал от паука на проверку состояния GameOver
     * */
    connect(spider, &Spider::signalCheckGameOver, this, &Widget::slotGameOver);

    /** Инициализируем таймер и вызываем слот обработки сигнала таймера
     * у Треугольника 100 раз в секунду.
     * Управляя скоростью отсчётов, соответственно управляем скоростью
     * изменения состояния графической сцены
     * */
    connect(timer, &QTimer::timeout, triangle, &Triangle::slotGameTimer);
    timer->start(1000 / 100);

    /** Раз в секунду отсылаем сигнал на создание яблока в игре
     * */
    connect(timerCreateApple, &QTimer::timeout, this, &Widget::slotCreateApple);
    timerCreateApple->start(1000);

    /** Подключаем сигнал от божьей коровки, в котором передаются Объекты, на которые
     * наткнулась божья коровка
     * */
    connect(triangle, &Triangle::signalCheckItem, this, &Widget::slotDeleteApple);

    ui->pushButton->setEnabled(false);

    gameState = GAME_STARTED;
}

void Widget::slotGameOver()
{
    /* Если игра окончена
     * Отключаем все таймеры
     * */
    timer->stop();
    timerCreateApple->stop();


    QMediaPlayer * m_player = new QMediaPlayer(this);       // Создаём плеер
    QMediaPlaylist * m_playlist = new QMediaPlaylist(m_player); // Создаём плейлист

    m_player->setPlaylist(m_playlist);      // Устанавливаем плейлист в плеер
    m_playlist->addMedia(QUrl("qrc:/game/gameover.wav")); // Добавляем аудио в плейлист
    m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);   // Проигрываем трек один раз
    m_player->play();   // Запускаем трек

    QMessageBox::warning(this,
                         "Game Over",
                         "Вы проиграли");
    /* Отключаем все сигналы от слотов
     * */
    disconnect(timerCreateApple, &QTimer::timeout, this, &Widget::slotCreateApple);
    disconnect(triangle, &Triangle::signalCheckItem, this, &Widget::slotDeleteApple);
    disconnect(spider, &Spider::signalCheckGameOver, this, &Widget::slotGameOver);
    /* И удаляем все объекты со сцены
     * */
    spider->deleteLater();
    triangle->deleteLater();

    foreach (QGraphicsItem *apple, apples) {
        scene->removeItem(apple);   // Удаляем со сцены
        apples.removeOne(apple);    // Удаляем из списка
        delete apple;               // Вообще удаляем
    }
    /* Активируем кнопку старта игры
     * */
    ui->pushButton->setEnabled(true);

    gameState = GAME_STOPED; // Устанавливаем состояние игры в GAME_STOPED
}

void Widget::slotPause()
{
    /* Выполняем проверку на состояние игры,
     * если игра не запущена, то игнорируем Паузу.
     * В противном случае или запускаем, или останавливаем все таймеры
     * */
    if(gameState == GAME_STARTED){
        if(timer->isActive()){
            timer->stop();
            timerCreateApple->stop();
            spider->pause();
        } else {
            timer->start(1000/100);
            timerCreateApple->start(1000);
            spider->pause();
        }
    }
}
