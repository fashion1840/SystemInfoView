#-------------------------------------------------
#
# Project created by QtCreator 2020-07-15T13:47:34
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SystemInfoView
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32{
SOURCES +=  WindowsSysInfo.cpp
HEADERS +=  WindowsSysInfo.h
LIBS += -ldxgi
}

macx{
SOURCES +=  MacxSysInfo.cpp
HEADERS +=  MacxSysInfo.h
}

unix{
SOURCES +=  LinuxSysInfo.cpp
HEADERS +=  LinuxSysInfo.h
}


SOURCES += main.cpp\
        SystemInfoView.cpp \
    ISystemInfoFactory.cpp \
    IMoveWidget.cpp

HEADERS  += SystemInfoView.h \
    ISystemInfoFactory.h \
    IMoveWidget.h

FORMS    += SystemInfoView.ui

RESOURCES += \
    Resources.qrc
