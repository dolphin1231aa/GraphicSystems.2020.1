#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    this->setWindowTitle("Божественная комбинация");
    setWindowIcon(QIcon(":/icon/corgi.png"));
    view = new View();
    ui->gridLayout_4->addWidget(view);

}

MainWindow::~MainWindow()
{
    delete ui;
}

