#-------------------------------------------------
#
# Project created by QtCreator 2016-12-28T23:21:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = EasyPlot
TEMPLATE = app


SOURCES += main.cpp\
        maingraph.cpp \
    qcustomplot.cpp

HEADERS  += maingraph.h \
    qcustomplot.h

FORMS    += maingraph.ui

QCUSTOMPLOT_USE_LIBRARY
