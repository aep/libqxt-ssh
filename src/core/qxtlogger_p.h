/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of the Common Public License, version 1.0, as published by
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
** <http://libqxt.sourceforge.net>  <foundation@libqxt.org>
**
****************************************************************************/

#ifndef QXTLOGGERPRIVATE_H
#define QXTLOGGERPRIVATE_H

#include "qxtlogger.h"
#include <QHash>

/*******************************************************************************
    QxtLoggerPrivate
    This is the d_ptr private class containing the actual data this library
    works with.
*******************************************************************************/
class QMutex;
class QxtLoggerPrivate : public QObject, public QxtPrivate<QxtLogger>
{
Q_OBJECT
QXT_DECLARE_PUBLIC(QxtLogger);
public:
    QxtLoggerPrivate();
    ~QxtLoggerPrivate();
    void setQxtLoggerEngineMinimumLevel(QxtLoggerEngine *engine, QxtLogger::LogLevel level);
    QHash<QString, QxtLoggerEngine*> map_logEngineMap;
    QMutex* mut_lock;

public slots:
    void log(QxtLogger::LogLevel, const QList<QVariant>&);
};

#endif // QXTLOGGERPRIVATE_H
