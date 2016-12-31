include(../defaults.pri)
TEMPLATE = app


# Check version
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


# Using Qt's core and gui module:
QT       += core gui svg


# Files we need:
SOURCES += main.cpp \
        mainwindow.cpp \
    utilz/textviewutilz.cpp \
    viewmodels/taskviewmodel.cpp \
    viewmodels/tasklistviewmodel.cpp \
    views/appspec/taskview.cpp \
    views/appspec/tasklistview.cpp \
    views/reusable/customcheckbox.cpp \
    views/reusable/customiconbutton.cpp \
    views/reusable/custommenubar.cpp \
    controller/tasklistctrl.cpp \
    views/appspec/taskeditview.cpp \
    controller/taskeditctrl.cpp \
    utilz/qanimationutilz.cpp

HEADERS  += mainwindow.h \
    utilz/textviewutilz.h \
    viewmodels/taskviewmodel.h \
    viewmodels/tasklistviewmodel.h \
    views/appspec/taskview.h \
    views/appspec/tasklistview.h \
    views/reusable/customcheckbox.h \
    views/reusable/customiconbutton.h \
    views/reusable/custommenubar.h \
    controller/tasklistctrl.h \
    views/appspec/taskeditview.h \
    controller/taskeditctrl.h \
    utilz/qanimationutilz.h

INCLUDEPATH += views/reusable \
               views/appspec \
               viewmodels \
               controller



# Libraries:
LIBS += -L../src/lib -ldotoo        # Using dotoolib with common dotoo stuff.

RESOURCES += \
    resources.qrc

