MODULE=QXT_KIT
include (../../config.pri)

VERSION = $$QXVERSION
TEMPLATE = lib
TARGET = QxtKit
DEPENDPATH += .
INCLUDEPATH += .
DEFINES += BUILD_QXT_KIT
QT = core




QXT_KIT                        += QxtSignalWaiter
QXT_HEADERS_QxtSignalWaiter     = QxtSignalWaiter.h
QXT_SOURCES_QxtSignalWaiter     = QxtSignalWaiter.cpp
QXT_STABILITY_QxtSignalWaiter   = 

QXT_KIT                        += QxtTrippleList
QXT_HEADERS_QxtTrippleList      = QxtTrippleList.h
QXT_STABILITY_QxtTrippleList    = 

QXT_KIT                        += QxtPairList
QXT_HEADERS_QxtPairList         = QxtPairList.h
QXT_STABILITY_QxtPairList       = 




include (../parts.pri)
HEADERS+=../../deploy/include/Qxt/qxtnamespace.h
