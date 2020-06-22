TEMPLATE += app
DESTDIR = $$PWD/build/
TARGET = crevis
OBJECTS_DIR = $$PWD/build/

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += $$PWD/src/main.cpp $$PWD/src/gui/window.cpp
INCLUDEPATH = $$PWD/include/