#include "mytimer.h"

MyTimer::MyTimer() {
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(myTimeout()));
}


void MyTimer::myStart(int msec, char side) {
    this->side = side;
    timer->start(msec);
}

void MyTimer::myTimeout() {
    emit my_timeout(side);
}

void MyTimer::stop() {
    timer->stop();
}


bool MyTimer::isActive() {
    return timer->isActive();
}

MyTimer::~MyTimer() {}

