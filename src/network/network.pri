INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += qxtjsonrpccall.h
HEADERS += qxtjsonrpcclient.h
HEADERS += qxtnetwork.h
HEADERS += qxtmail_p.h
HEADERS += qxtsmtp.h
HEADERS += qxtsmtp_p.h
HEADERS += qxtmailattachment.h
HEADERS += qxtmailmessage.h
HEADERS += qxtrpcpeer.h
HEADERS += qxttcpconnectionmanager.h
HEADERS += qxttcpconnectionmanager_p.h
HEADERS += qxtxmlrpccall.h
HEADERS += qxtxmlrpcclient.h
HEADERS += qxtxmlrpc_p.h

SOURCES += qxtjsonrpccall.cpp
SOURCES += qxtjsonrpcclient.cpp
SOURCES += qxtmailattachment.cpp
SOURCES += qxtmailmessage.cpp
SOURCES += qxtrpcpeer.cpp
SOURCES += qxtsmtp.cpp
SOURCES += qxttcpconnectionmanager.cpp
SOURCES += qxtxmlrpccall.cpp
SOURCES += qxtxmlrpcclient.cpp
SOURCES += qxtxmlrpc_p.cpp



contains(DEFINES,HAVE_OPENSSL){
 HEADERS += qxtsshchannel.h
 HEADERS += qxtsshchannel_p.h
 HEADERS += qxtsshclient.h
 HEADERS += qxtsshclient_p.h
 HEADERS += qxtsshprocess.h
 HEADERS += qxtsshtcpsocket.h

 SOURCES += qxtsshchannel.cpp
 SOURCES += qxtsshclient.cpp
 SOURCES += qxtsshprocess.cpp
 SOURCES += qxtsshtcpsocket.cpp	
}

