#-------------------------------------------------
#
# Project created by QtCreator 2022-10-04T16:08:10
#
#-------------------------------------------------

QT       += core gui serialport printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ArduinoPlotterInterface
TEMPLATE = app


SOURCES += main.cpp\
        arduplot.cpp \
    plotwin.cpp \
    qcustomplot.cpp

HEADERS  += arduplot.h \
    plotwin.h \
    qcustomplot.h

FORMS    += arduplot.ui \
    plotwin.ui

DISTFILES += \
    icon.png \
    Recorded_data/record.csv

