#-------------------------------------------------
#
# Project created by QtCreator 2011-03-09T15:15:10
#
#-------------------------------------------------

QT       += core gui

TARGET = VECalendar
TEMPLATE = app

RESOURCES     = icons.qrc

SOURCES += main.cpp\
        mainwindow.cpp \
        addmoddialog.cpp \
        calendarevent.cpp \
    calendar.cpp \
    dayeventfilterproxy.cpp \
    eventlistproxy.cpp

HEADERS  += mainwindow.h \
         calendarevent.h \
         addmoddialog.h \
    calendar.h \
    dayeventfilterproxy.h \
    eventlistproxy.h

FORMS    += mainwindow.ui \
    addmoddialog.ui
