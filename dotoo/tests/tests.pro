include(../defaults.pri)
TEMPLATE = app

QT += core
QT -= gui

CONFIG += c++11

CONFIG += console
CONFIG -= app_bundle


SOURCES += main.cpp

LIBS += -L../src -ldotoolib
