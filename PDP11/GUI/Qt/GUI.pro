#-------------------------------------------------
#
# Project created by QtCreator 2019-01-22T23:27:21
#
#-------------------------------------------------

QMAKE_EXTRA_TARGETS += before_build makefilehook

makefilehook.target = $(MAKEFILE)
makefilehook.depends = .beforebuild

PRE_TARGETDEPS += .beforebuild

before_build.target = .beforebuild
before_build.depends = FORCE
before_build.commands = chcp 1251

QT       += core gui widgets

TARGET = GUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17
QMAKE_CXXFLAGS += -std:c++latest

INCLUDEPATH += ../../

SOURCES += \
        main.cpp \
        MainWindow.cpp \
    RegistersModel.cpp \
    Qemulator.cpp \
    QLog.cpp \
    EmullatorLogModel.cpp \
    RomModel.cpp \
    MemoryDumpWidget.cpp \
    MemoryDumpModel.cpp \
    VideoController.cpp

HEADERS += \
        MainWindow.h \
    RegistersModel.h \
    Qemulator.h \
    QLog.h \
    EmullatorLogModel.h \
    RomModel.h \
    MemoryDumpWidget.h \
    MemoryDumpModel.h \
    VideoController.h

FORMS += \
        MainWindow.ui \
    memorydumpwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/lib/ -lPDP11

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/PDP11.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/lib/libPDP11.a
