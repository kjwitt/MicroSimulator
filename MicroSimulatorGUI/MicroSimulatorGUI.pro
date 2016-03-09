#-------------------------------------------------
#
# Project created by QtCreator 2016-01-20T21:24:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MicroSimulatorGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    clear_check.cpp \
    assembler.c \
    codeeditor.cpp \
    alu.cpp \
    controller.cpp \
    executive.cpp \
    jump.cpp \
    Memory.cpp \
    statusflags.cpp

HEADERS  += mainwindow.h \
    clear_check.h \
    assembler.h \
    hexconstants.h \
    codeeditor.h \
    alu.h \
    constants.h \
    controller.h \
    executive.h \
    jump.h \
    Memory.h \
    sr.h \
    statusflags.h

FORMS    += mainwindow.ui \
    clear_check.ui

RESOURCES += \
    images.qrc

RC_FILE = myapp.rc
