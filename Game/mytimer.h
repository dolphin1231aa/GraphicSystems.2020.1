#ifndef MYTIMER_H
#define MYTIMER_H

#include <QTimer>

class MyTimer: public QTimer {
    Q_OBJECT
public:
    MyTimer();
    ~MyTimer();
    bool isActive();

public slots:
    void myStart(int, char);
    void stop();

private slots:
    void myTimeout();

signals:
    void my_timeout(char);
private:
    char side;
    QTimer* timer;
};

#endif // MYTIMER_H
