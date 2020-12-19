#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <sprite.h>

#include <QMainWindow>
#include <QGraphicsScene>
#include <shuriken.h>
#include <grob.h>
#include <QDebug>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <bg.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void shurikenspawn(QString state);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void creategrob();
    void deletegrob(QGraphicsItem * item);
    void deleteshuriken(QGraphicsItem *item);
private:
    bg *backG;
    QGraphicsPixmapItem *item;
    QPixmap *background;
   QList<QGraphicsItem *> grobs;
   QList<QGraphicsItem *> shurikens;
     QTimer *timer;
    sprite *naruto;
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

};
#endif // MAINWINDOW_H
