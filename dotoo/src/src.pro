include(../defaults.pri)
TEMPLATE = lib

# Using Qt's core and sql module:
QT += core sql network
QT -= gui

TARGET = dotoolib

DEFINES += COMPILE_LIBRARY

HEADERS += \
    project/libsymbolsexport.h \
    models/interface/task.h \
    models/interface/decl/taskdecl.h \
    models/interface/person.h \
    models/interface/decl/persondecl.h \
    models/interface/decl/projectdecl.h \
    models/implementation/taskimpl.h \
    models/interface/types/persontypes.h \
    models/interface/types/commontypes.h \
    models/interface/decl/commondecl.h \
    models/interface/types/tasktypes.h \
    models/implementation/personimpl.h \
    modelparser/person_json.h \
    modelparser/taskjson.h \
    data/utils/sqlrequest.h \
    data/interface/datalyr_person.h \
    data/interface/datalyr_types.h \
    data/implementation/datalyr_personsql.h \
    data/interface/datalyr_task.h \
    data/implementation/datalyr_tasksql.h \
    modelparser/interface/bytestreampersonparser.h \
    modelparser/interface/bytestreamtaskparser.h \
    ext/parsing/json.h \
    data/interface/asyncdatalyr_task.h \
    data/implementation/asyncdatalyr_taskhttp.h \
    data/utilz/http.h
    #ext/parsing/route.h

SOURCES += \
    models/implementation/taskimpl.cpp \
    models/implementation/personimpl.cpp \
    models/interface/task.cpp \
    models/interface/person.cpp \
    modelparser/person_json.cpp \
    modelparser/taskjson.cpp \
    data/utils/sqlrequest.cpp \
    data/implementation/datalyr_personsql.cpp \
    data/implementation/datalyr_tasksql.cpp \
    data/implementation/asyncdatalyr_taskhttp.cpp
    #ext/parsing/route.cpp

INCLUDEPATH += \
    project \
    models/interface \
    models/implementation \
    persistence \
    modelparser \
    ext
