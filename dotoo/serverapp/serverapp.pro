include(../defaults.pri)
TEMPLATE = app


# Using ONLY Qt's core module:
QT += core network sql
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
    httprequesthandleraccubody.cpp \
    rest/persons/deletepersonhandler.cpp \
    rest/persons/changepersonhandler.cpp \
    rest/tasks/createtaskhandler.cpp \
    rest/tasks/changetaskhandler.cpp \
    rest/tasks/deletetaskhandler.cpp \
    rest/tasks/getalltaskshandler.cpp \
    rest/tasks/gettaskhandler.cpp

HEADERS += \
    httprequesthandler.h \
    httprequestrouter.h \
    rest/persons/getallpersonshandler.h \
    utilz/tohttpcode.h \
    rest/persons/createpersonhandler.h \
    rest/persons/getpersonhandler.h \
    httprequesthandleraccubody.h \
    rest/persons/deletepersonhandler.h \
    utilz/uriutilz.h \
    rest/persons/changepersonhandler.h \
    rest/tasks/createtaskhandler.h \
    rest/tasks/changetaskhandler.h \
    rest/tasks/deletetaskhandler.h \
    rest/tasks/getalltaskshandler.h \
    rest/tasks/gettaskhandler.h

INCLUDEPATH += ../qhttpserver/src

# Libraries:
LIBS += -L../src/lib -L../qhttpserver/lib -ldotoo -lqhttpserver
