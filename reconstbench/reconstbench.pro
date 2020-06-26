TEMPLATE = app
CONFIG += c++14
CONFIG -= app_bundle
#CONFIG -= qt

TARGET = reconstbench

ROOT_FOLDER = $$PWD/..
BUILD_FOLDER = $$ROOT_FOLDER/../build

OBJECTS_DIR = $$BUILD_FOLDER/$$TARGET
MOC_DIR = $$BUILD_FOLDER/$$TARGET
DESTDIR = $$BUILD_FOLDER/$$TARGET

SOURCES += \
        createmrcsetup.cpp \
        main.cpp \
        mrcreconstruction.cpp

## Libraries
INCLUDEPATH += $$ROOT_FOLDER $$ROOT_FOLDER/..
DEPENDPATH += $$ROOT_FOLDER $$ROOT_FOLDER/..

INCLUDEPATH += $$ROOT_FOLDER/../ctk
DEPENDPATH += $$ROOT_FOLDER/../ctk
LIBS += -L$$BUILD_FOLDER/libs -lctk
PRE_TARGETDEPS += $$BUILD_FOLDER/libs/libctk.a

LIBS += -L$$BUILD_FOLDER/libs -lfilesys
PRE_TARGETDEPS += $$BUILD_FOLDER/libs/libfilesys.a

INCLUDEPATH += $$ROOT_FOLDER/../benchmark
DEPENDPATH += $$ROOT_FOLDER/../benchmark
LIBS += -L$$BUILD_FOLDER/libs -lbenchlib
PRE_TARGETDEPS += $$BUILD_FOLDER/libs/libbenchlib.a

unix:!macx {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}
macx: {
    QT_CONFIG -= no-pkg-config
    CONFIG += link_pkgconfig
    PKG_CONFIG = /usr/local/bin/pkg-config
    PKGCONFIG += opencv4
#    PKGCONFIG += tesseract
    PKGCONFIG += zbar ilmbase
}

HEADERS += \
    createmrcsetup.h \
    mrcreconstruction.h

INCLUDEPATH += $$ROOT_FOLDER/../lab-lib-uniqode/
DEPENDPATH += $$ROOT_FOLDER/../lab-lib-uniqode/
LIBS += -L$$BUILD_FOLDER/libs -luniqode
PRE_TARGETDEPS += $$BUILD_FOLDER/libs/libuniqode.a

LIBS += -L$$BUILD_FOLDER/libs -lqtjsonfs
PRE_TARGETDEPS += $$BUILD_FOLDER/libs/libqtjsonfs.a
