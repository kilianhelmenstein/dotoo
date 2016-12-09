include(../defaults.pri)
TEMPLATE = app


# Check version
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


# Using Qt's core and gui module:
QT       += core gui


# Files we need:
SOURCES += main.cpp \
        mainwindow.cpp \
    views/taskview.cpp

HEADERS  += mainwindow.h \
    views/taskview.h



# Libraries:
LIBS += -L../src -ldotoolib     # Using dotoolib with common dotoo stuff.
