#-------------------------------------------------
#
# Project created by QtCreator 2019-11-21T17:48:20
#
#-------------------------------------------------

QT       += core gui
RC_ICONS = sketchpad.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sketchpad
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    centerwidget.cpp \
    deletebox.cpp \
    ellipse.cpp \
    line.cpp \
    rectangle.cpp \
    selferaser.cpp \
    selfline.cpp \
    shape.cpp \
    triangle.cpp

HEADERS += \
        mainwindow.h \
    centerwidget.h \
    deletebox.h \
    ellipse.h \
    line.h \
    rectangle.h \
    selferaser.h \
    selfline.h \
    shape.h \
    triangle.h

RESOURCES += \
    images.qrc
