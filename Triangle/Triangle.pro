#-------------------------------------------------
#
# Project created by QtCreator 2015-09-16T13:17:29
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Triangle
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    triangle.cpp \
    apple.cpp \
    spider.cpp

HEADERS  += widget.h \
    triangle.h \
    apple.h \
    spider.h

FORMS    += widget.ui

RESOURCES += \
    resources/game.qrc
