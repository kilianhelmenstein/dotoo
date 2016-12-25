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
    views/tasklistview.cpp \
    views/customiconbutton.cpp

HEADERS  += mainwindow.h \
    views/taskview.h \
    viewmodels/taskviewmodel.h \
    views/customcheckbox.h \
    utilz/textviewutilz.h \
    viewmodels/tasklistviewmodel.h \
    views/tasklistview.h \
    views/customiconbutton.h



# Libraries:
LIBS += -L../src/lib -ldotoo        # Using dotoolib with common dotoo stuff.

RESOURCES += \
    resources.qrc

