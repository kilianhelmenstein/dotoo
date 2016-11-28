include(../defaults.pri)
TEMPLATE = app


# Using ONLY Qt's core module:
QT += core network
QT -= gui


# This will advice the compiler to use c++11 features:
CONFIG += c++11


TARGET = serverapp
CONFIG += console
CONFIG -= app_bundle


# Files we need:
SOURCES += main.cpp \
    httprequestrouter.cpp \
    rest/persons/getallpersonshandler.cpp \
    rest/persons/createpersonhandler.cpp \
    rest/persons/getpersonhandler.cpp \
    httprequesthandleraccubody.cpp

INCLUDEPATH += ../qhttpserver/src

# Libraries:
LIBS += -L../src -L../qhttpserver/lib -ldotoolib -lqhttpserver

HEADERS += \
    httprequesthandler.h \
    httprequestrouter.h \
    rest/persons/getallpersonshandler.h \
    utilz/tohttpcode.h \
    rest/persons/createpersonhandler.h \
    rest/persons/getpersonhandler.h \
    httprequesthandleraccubody.h
