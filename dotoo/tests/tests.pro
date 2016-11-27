include(../defaults.pri)
TEMPLATE = app

QT += core testlib
QT -= gui

CONFIG += c++11

CONFIG += console
CONFIG -= app_bundle


SOURCES += main.cpp \
    testdatalyr_personsql.cpp

LIBS += -L../src -ldotoolib

HEADERS += \
    testdatalyr_personsql.h
