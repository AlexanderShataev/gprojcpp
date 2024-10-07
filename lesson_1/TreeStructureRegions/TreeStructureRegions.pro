QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += src/*.cpp

HEADERS += src/*.h

FORMS += src/*.ui

DESTDIR = $$PWD/bin

BUILDPATH = $$PWD/build

MOC_DIR = $$BUILDPATH
RCC_DIR = $$BUILDPATH
UI_DIR = $$BUILDPATH
OBJECTS_DIR = $$BUILDPATH

