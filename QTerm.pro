#-------------------------------------------------
#
# Project created by QtCreator 2014-12-05T16:07:28
#
#-------------------------------------------------

QT       += core gui \
                network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTerm
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qtermhistory.cpp \
    qterminal.cpp \
    settingdialog.cpp

HEADERS  += mainwindow.h \
    qtermhistory.h \
    qterminal.h \
    settingdialog.h \
    telnetIAC.h

RESOURCES += \
    uiPic.qrc
