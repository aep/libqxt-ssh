MODULE=QXT_MEDIA
include (../../config.pri)

VERSION = $$QXVERSION
TEMPLATE = lib
TARGET = QxtMedia
DEPENDPATH += .
INCLUDEPATH += .
DEFINES += BUILD_QXT_MEDIA
QT = core gui


QXT_MEDIA                       += QxtAVFile
QXT_HEADERS_QxtAVFile        	 = QxtAVFile.h
QXT_SOURCES_QxtAVFile	 	 = QxtAVFile.cpp
QXT_STABILITY_QxtAVFile      	 =


QXT_MEDIA                       += QxtSdlWidget
QXT_HEADERS_QxtSdlWidget       	 = QxtSdlWidget.h
QXT_SOURCES_QxtSdlWidget 	 = QxtSdlWidget.cpp
QXT_STABILITY_QxtSdlWidgt      	 =

QXT_MEDIA                       += QxtAVPlayer
QXT_HEADERS_QxtAVPlayer       = QxtAVPlayer.h
QXT_SOURCES_QxtAVPlayer 	 = QxtAVPlayer.cpp
QXT_STABILITY_QxtAudioPlayer     =


LIBS+= -lavcodec -lavformat -lportaudio -lSoundTouch -lSDL

include (../parts.pri)

QMAKE_CXXFLAGS+= -O2

