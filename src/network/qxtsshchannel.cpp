/****************************************************************************
 **
 ** Copyright (C) Qxt Foundation. Some rights reserved.
 **
 ** This file is part of the QxtWeb module of the Qxt library.
 **
 ** This library is free software; you can redistribute it and/or modify it
 ** under the terms of the Common Public License, version 1.0, as published
 ** by IBM, and/or under the terms of the GNU Lesser General Public License,
 ** version 2.1, as published by the Free Software Foundation.
 **
 ** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
 ** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 ** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
 ** FITNESS FOR A PARTICULAR PURPOSE.
 **
 ** You should have received a copy of the CPL and the LGPL along with this
 ** file. See the LICENSE file and the cpl1.0.txt/lgpl-2.1.txt files
 ** included with the source distribution for more information.
 ** If you did not receive a copy of the licenses, contact the Qxt Foundation.
 **
 ** <http://libqxt.org>  <foundation@libqxt.org>
 **
 ****************************************************************************/

/*!
    \class QxtSshChannel
    \inmodule QxtNetwork
    \brief The QxtSshChannel class is an abstract base for channels over a QxtSshClient connection

    it implements a QIODevice, including the readyRead signal
*/

/*!
 * \fn QxtSshChannel::connected()
 *
 * this signal is emited when the channel is established and ready for use.
 */

#include "qxtsshchannel.h"
#include "qxtsshchannel_p.h"

QxtSshChannel::QxtSshChannel(QxtSshClient * parent)
    :QIODevice(parent)
    ,d(new QxtSshChannelPrivate(this,parent)){
}


QxtSshChannelPrivate::QxtSshChannelPrivate(QxtSshChannel *_p,QxtSshClient * c)
    :QObject(0)
    ,p(_p)
    ,d_client(c)
    ,d_channel(0)
    ,d_session(d_client->d->d_session)
    ,d_read_stream_id(0)
    ,d_write_stream_id(0)
    ,d_state(0)
{
}

/*!
    \reimp
*/
qint64 QxtSshChannel::readData(char* buff, qint64 len) {
    ssize_t ret=libssh2_channel_read_ex(d->d_channel, d->d_read_stream_id,buff, len);
    if(ret<0){
        if(ret==LIBSSH2_ERROR_EAGAIN){
            return 0;
        }else{
#ifdef QXT_DEBUG_SSH
            qDebug()<<"read err"<<ret;
#endif
            return -1;
        }
    }
    return ret;
}

/*!
    \reimp
*/
qint64 QxtSshChannel::writeData(const char* buff, qint64 len){
    ssize_t ret=libssh2_channel_write_ex(d->d_channel, d->d_write_stream_id,buff, len);
    if(ret<0){
        if(ret==LIBSSH2_ERROR_EAGAIN){
            return 0;
        }else{
#ifdef QXT_DEBUG_SSH
            qDebug()<<"write err"<<ret;
#endif
            return -1;
        }
    }
    return ret;
}


bool QxtSshChannelPrivate::activate(){
    //session
    if(d_state==1){
        d_channel=libssh2_channel_open_session(d_session);
        if(d_channel==NULL){
            if(libssh2_session_last_error(d_session,NULL,NULL,0)==LIBSSH2_ERROR_EAGAIN) {
                return true;
            }else{
                return false;
            }
        }
#ifdef QXT_DEBUG_SSH
        qDebug("session opened");
#endif
        d_state=2;
        return activate();

    //transition to allow early cmd
    }else if (d_state==2){
        if(!d_next_actions.isEmpty()){
            d_state=d_next_actions.takeFirst();
            return activate();
        }else{
            return true;
        }

    //request pty
    }else if (d_state==5){
        int r=libssh2_channel_request_pty(d_channel,d_pty.data());
        if(r){
            if(r==LIBSSH2_ERROR_EAGAIN){
                return true;
            }else{
                qWarning("QxtSshChannel: pty allocation failed");
                return false;
            }
        }
#ifdef QXT_DEBUG_SSH
        qDebug("pty opened");
#endif
        d_state=2;
        return activate();

    //start
    }else if (d_state==3){
        int r=libssh2_channel_exec(d_channel,qPrintable(d_cmd));
        if(r){
            if(r==LIBSSH2_ERROR_EAGAIN){
                return true;
            }else{
#ifdef QXT_DEBUG_SSH
                qDebug("exec failed");
#endif
                return false;
            }
        }
#ifdef QXT_DEBUG_SSH
        qDebug("exec opened");
#endif
        p->setOpenMode(QIODevice::ReadWrite);
        d_state=66;
        emit p->connected();
        return true;

    //start shell
    }else if (d_state==4){
        int r=libssh2_channel_shell(d_channel);
        if(r){
            if(r==LIBSSH2_ERROR_EAGAIN){
                return true;
            }else{
#ifdef QXT_DEBUG_SSH
                qDebug("exec failed");
#endif
                return false;
            }
        }
#ifdef QXT_DEBUG_SSH
        qDebug("shell opened");
#endif
        p->setOpenMode(QIODevice::ReadWrite);
        d_state=9999;
        emit p->connected();
        return true;

    // tcp channel
    }else if (d_state==10){
        d_channel=libssh2_channel_direct_tcpip(d_session, qPrintable(d_host),d_port);
        if(d_channel==NULL){
            if(libssh2_session_last_error(d_session,NULL,NULL,0)==LIBSSH2_ERROR_EAGAIN) {
                return true;
            }else{
                return false;
            }
        }
#ifdef QXT_DEBUG_SSH
        qDebug("tcp channel opened");
#endif
        p->setOpenMode(QIODevice::ReadWrite);
        d_state=9999;
        return activate();

    //read channel
    }else if (d_state==9999){
        emit p->readyRead();
    }
    return true;
}


void QxtSshChannelPrivate::openSession(){
    if(d_state!=0){
        return;
    }
    d_state=1;
    activate();
}

void QxtSshChannelPrivate::requestPty(QByteArray pty){
    if(d_state>5){
        return;
    }
    d_pty=pty;
    if(d_state==2){
        d_state=5;
        activate();
    }else{
        if(!d_next_actions.contains(5))
            d_next_actions.append(5);
    }
}

void QxtSshChannelPrivate::start(QString cmd){
    if(d_state>5){
        return;
    }
    d_cmd=cmd;
    if(d_state==2){
        d_state=3;
        activate();
    }else{
        if(!d_next_actions.contains(3))
            d_next_actions.append(3);
    }
}
void QxtSshChannelPrivate::startShell(){
    if(d_state>5){
        return;
    }
    if(d_state==2){
        d_state=4;
        activate();
    }else{
        if(!d_next_actions.contains(4))
            d_next_actions.append(4);
    }
}



void QxtSshChannelPrivate::openTcpSocket(QString host,qint16 port){
    if(d_state!=0){
        return;
    }
    d_host=host;
    d_port=port;
    d_state=10;
    activate();
}
