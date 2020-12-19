#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::shurikenspawn(QString state)
{


     background = new QPixmap(":/naruto/img/PixelArt.png");


    qDebug()<<"kek";
    shuriken *kek = new shuriken(state);




    kek->setPos(naruto->x(),naruto->y());

    scene->addItem(kek);

    shurikens.push_back(kek);
    connect(kek,&shuriken::destr,this,&MainWindow::deletegrob);
    connect(kek,&shuriken::selfdstr,this,&MainWindow::deleteshuriken);


}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    timer = new QTimer();

   this->resize(1920,1080);
    this->setFixedSize(1920,1080);

    scene->setSceneRect(-250,-250,500,500);

     ui->graphicsView->setScene(scene);
     ui->graphicsView->setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
        ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
        ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        backG = new bg();

        scene->addItem(backG);
    naruto = new sprite();
    scene->addItem(naruto);
    naruto->setPos(100,100);
    naruto->setScale(3);
      connect(naruto,&sprite::udar,this,&MainWindow::shurikenspawn);
      connect(timer,&QTimer::timeout,this,&MainWindow::creategrob);


      timer->start(3000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::creategrob()
{
    grob *kek = new grob();
    kek->setPos((qrand() % (1080)) * ((qrand()%2 == 1)?1:-1),
              (qrand() % (720)) * ((qrand()%2 == 1)?1:-1));
    scene->addItem(kek);
    grobs.push_back(kek);



}

void MainWindow::deletegrob(QGraphicsItem *item)
{
    foreach (QGraphicsItem *grob, grobs) {
            if(grob == item){
                scene->removeItem(grob);   // Удаляем со сцены
                grobs.removeOne(item);     // Удаляем из списка
                delete grob;               // Вообще удаляем

            }
    }
}

void MainWindow::deleteshuriken(QGraphicsItem *item)
{
    foreach (QGraphicsItem *shuriken, shurikens) {
            if(shuriken == item){
                scene->removeItem(shuriken);   // Удаляем со сцены
                shurikens.removeOne(item);     // Удаляем из списка
                delete shuriken;               // Вообще удаляем

            }
    }
}


