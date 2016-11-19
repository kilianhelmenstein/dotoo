include(../defaults.pri)
TEMPLATE = app


# Using ONLY Qt's core module:
QT += core
QT -= gui


# This will advice the compiler to use c++11 stuff:
CONFIG += c++11


TARGET = serverapp
CONFIG += console
CONFIG -= app_bundle


# Files we need:
SOURCES += main.cpp


# Libraries:
LIBS += -L../src -ldotoolib
