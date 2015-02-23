#-------------------------------------------------
#
# Project created by QtCreator 2015-01-21T20:38:45
#
#-------------------------------------------------

QT       += core gui network xml widgets

TARGET = client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    client.cpp \
    xmlreader.cpp \
    question.cpp \
    xmlgenerator.cpp

HEADERS  += mainwindow.h \
    client.h \
    xmlreader.h \
    question.h \
    xmlgenerator.h

FORMS    += mainwindow.ui
