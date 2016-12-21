include(../defaults.pri)
TEMPLATE = app


# Check version
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


# Using Qt's core and gui module:
QT       += core gui svg


# Files we need:
SOURCES += main.cpp \
        mainwindow.cpp \
    views/taskview.cpp \
    viewmodels/taskviewmodel.cpp \
    views/customcheckbox.cpp \
    utilz/textviewutilz.cpp \
    viewmodels/tasklistviewmodel.cpp \
    views/tasklistview.cpp

HEADERS  += mainwindow.h \
    views/taskview.h \
    viewmodels/taskviewmodel.h \
    views/customcheckbox.h \
    utilz/textviewutilz.h \
    viewmodels/tasklistviewmodel.h \
    views/tasklistview.h



# Libraries:
LIBS += -L../src -ldotoolib     # Using dotoolib with common dotoo stuff.

RESOURCES += \
    resources.qrc

Release:DESTDIR = release
Release:OBJECTS_DIR = release/.obj
Release:MOC_DIR = release/.moc
Release:RCC_DIR = release/.rcc
Release:UI_DIR = release/.ui

Debug:DESTDIR = debug
Debug:OBJECTS_DIR = debug/.obj
Debug:MOC_DIR = debug/.moc
Debug:RCC_DIR = debug/.rcc
Debug:UI_DIR = debug/.ui
