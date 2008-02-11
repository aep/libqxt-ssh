/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtGui module of the Qt eXTension library
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
** <http://libqxt.sourceforge.net>  <foundation@libqxt.org>
**
****************************************************************************/
#include "qxtapplication.h"
#include "qxtapplication_p.h"
#include "qxtnativeeventfilter.h"

QxtApplication::QxtApplication(Display* display, Qt::HANDLE visual, Qt::HANDLE colormap)
    : QApplication(display, visual, colormap)
{
}

QxtApplication::QxtApplication(Display* display, int& argc, char** argv, Qt::HANDLE visual, Qt::HANDLE colormap)
    : QApplication(display, argc, argv, visual, colormap)
{
}

/*!
    \reimp
 */
bool QxtApplication::x11EventFilter(XEvent* event)
{
    foreach (QxtNativeEventFilter* filter, qxt_d().nativeFilters)
    {
        if (filter && filter->x11EventFilter(event))
            return true;
    }
    return QApplication::x11EventFilter(event);
}
