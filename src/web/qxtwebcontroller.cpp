/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtWeb  module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of th Common Public License, version 1.0, as published by
** IBM.
**
** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
** FITNESS FOR A PARTICULAR PURPOSE.
**
** You should have received a copy of the CPL along with this file.
** See the LICENSE file and the cpl1.0.txt file included with the source
** distribution for more information. If you did not receive a copy of the
** license, contact the Qxt Foundation.
**
** <http://libqxt.org>  <foundation@libqxt.org>
**
****************************************************************************/
#include "qxtwebcontroller.h"
#include "qxtwebcore.h"
#include <QStringList>
#include <QDebug>
#include <QCoreApplication>
#include <QUrl>

QString QxtWebController::WebRoot()
{

    return QCoreApplication::applicationDirPath()+"/../";
}


QxtWebController::QxtWebController(QString name):QObject(QCoreApplication::instance())
{
    stream_m=0;
    setObjectName(name);
}


QTextStream & QxtWebController::echo()
{
    static QTextStream  nullstream;


    if (!stream_m)
    {
        qWarning("QxtWebController::echo() no stream open");
        return nullstream;
    }
    return *stream_m;
}
QByteArray & QxtWebController::buffer()
{
    static QByteArray  nullbuffer;

    if (!buff_m)
    {
        qWarning("QxtWebController::buffer() no buffer open");
        return nullbuffer;
    }
    return *buff_m;
}


QString QxtWebController::self()
{
    return "/"+objectName();
}


int QxtWebController::invoke(QxtWebStatelessConnection* t)
{
    QList<QString> args_d = t->request().path().split('/');

    ///--------------find action ------------------
    QByteArray action="index";
    if (args_d.count()>2)
    {
        action=args_d.at(2).toUtf8();
        if (action.trimmed().isEmpty())action="index";
    }
    else if (args_d.count()>1)
        action="index";


    if (args_d.count()>3)
    {
        args_d.removeFirst();
        args_d.removeFirst();
        args_d.removeFirst();
    }
    else
        args_d.clear();

    QStringList args=args_d;

    QByteArray buffer;
    QTextStream strm (&buffer);
    stream_m=  &strm;
    buff_m=  &buffer;


    int retVal=preInvoke();
    if(retVal!=0)
        return retVal;

    retVal=666;
    if (args.count()>8)
    {
        if (!QMetaObject::invokeMethod(this, action,Q_RETURN_ARG(int, retVal) ,
                                       Q_ARG(QString, args.at(0)),Q_ARG(QString, args.at(1)),Q_ARG(QString, args.at(2)),Q_ARG(QString, args.at(3))
                                       ,Q_ARG(QString, args.at(4)),Q_ARG(QString, args.at(5)),Q_ARG(QString, args.at(6)),Q_ARG(QString, args.at(8))))
        {
            retVal=4042; ///FIXME: the return value of the invoke has a meaning, handle it!
        }
    }
    else if (args.count()>7)
    {
        if (!QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ,
                                       Q_ARG(QString, args.at(0)),Q_ARG(QString, args.at(1)),Q_ARG(QString, args.at(2)),Q_ARG(QString, args.at(3))
                                       ,Q_ARG(QString, args.at(4)),Q_ARG(QString, args.at(5)),Q_ARG(QString, args.at(6)),Q_ARG(QString, args.at(7))
                                      ))
        {
            retVal=4042;
        }

    }
    else if (args.count()>6)
    {
        if ( !QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ,
                                        Q_ARG(QString, args.at(0)),Q_ARG(QString, args.at(1)),Q_ARG(QString, args.at(2)),Q_ARG(QString, args.at(3))
                                        ,Q_ARG(QString, args.at(4)),Q_ARG(QString, args.at(5)),Q_ARG(QString, args.at(6))
                                       ))
        {
            retVal=4042;
        }
    }
    else if (args.count()>5)
    {
        if (!QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ,
                                       Q_ARG(QString, args.at(0)),Q_ARG(QString, args.at(1)),Q_ARG(QString, args.at(2)),Q_ARG(QString, args.at(3))
                                       ,Q_ARG(QString, args.at(4)),Q_ARG(QString, args.at(5))
                                      ))
        {
            retVal=4042;
        }
    }
    else if ( args.count()>4)
    {
        if ( !QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ,
                                        Q_ARG(QString, args.at(0)),Q_ARG(QString, args.at(1)),Q_ARG(QString, args.at(2)),Q_ARG(QString, args.at(3))
                                        ,Q_ARG(QString, args.at(4))
                                       ))
        {
            retVal=4042;
        }
    }
    else if (args.count()>3)
    {
        if ( !QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ,
                                        Q_ARG(QString, args.at(0)),Q_ARG(QString, args.at(1)),Q_ARG(QString, args.at(2)),Q_ARG(QString, args.at(3))
                                       ))
        {
            retVal=4042;
        }
    }
    else if (args.count()>2)
    {
        if ( !QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ,
                                        Q_ARG(QString, args.at(0)),Q_ARG(QString, args.at(1)),Q_ARG(QString, args.at(2))
                                       ))
            retVal=4042;
    }
    else if (args.count()>1)
    {
        if ( !QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ,
                                        Q_ARG(QString, args.at(0)),Q_ARG(QString, args.at(1))
                                       ))
            retVal=4042;
    }
    else if (args.count()>0)
    {
        if ( !QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ,Q_ARG(QString, args.at(0))))
            retVal=4042;
    }
    else
    {
        if ( !QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ))
        {
            retVal=4042;
        }
    }



    if(retVal!=0)
        return retVal;
    retVal=postInvoke();



    stream_m->flush ();

    stream_m=0;
    buff_m=0;

    if(buffer.size())
        QxtWebLegacyEngine::send(buffer);


    return retVal;
};




int QxtWebController::postInvoke()
{
    return 0;
}

int QxtWebController::preInvoke()
{
    return 0;
}


