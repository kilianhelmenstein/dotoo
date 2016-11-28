include(../defaults.pri)
TEMPLATE = app

QT += core testlib
QT -= gui

CONFIG += c++11

CONFIG += console
CONFIG -= app_bundle


SOURCES += main.cpp \
    testdatalyr_personsql.cpp \
    modelparser/testjsontaskparser.cpp \
    modelparser/testjsonpersonparser.cpp

HEADERS += \
    testdatalyr_personsql.h \
    modelparser/testjsontaskparser.h \
    modelparser/testjsonpersonparser.h

LIBS += -L../src -ldotoolib
