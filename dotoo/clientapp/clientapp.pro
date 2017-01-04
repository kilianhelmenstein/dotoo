include(../defaults.pri)
TEMPLATE = app


# Check version
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


# Using Qt's core and gui module:
QT       += core gui svg

TRANSLATIONS = lang/dotoo_en.ts  lang/dotoo_de.ts

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
    utilz/qanimationutilz.cpp \
    viewmodels/personviewmodel.cpp \
    viewmodels/personlistviewmodel.cpp \
    views/appspec/personview.cpp \
    views/appspec/personlistview.cpp \
    views/appspec/personeditview.cpp \
    controller/personeditctrl.cpp \
    controller/personlistctrl.cpp

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
    utilz/qanimationutilz.h \
    viewmodels/personviewmodel.h \
    viewmodels/personlistviewmodel.h \
    views/appspec/personview.h \
    views/appspec/personlistview.h \
    views/appspec/personeditview.h \
    controller/personeditctrl.h \
    controller/personlistctrl.h

INCLUDEPATH += views/reusable \
               views/appspec \
               viewmodels \
               controller



# Libraries:
LIBS += -L../src/lib -ldotoo        # Using dotoolib with common dotoo stuff.

RESOURCES += \
    resources.qrc

