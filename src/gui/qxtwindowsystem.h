/****************************************************************************
 **
 ** Copyright (C) Qxt Foundation. Some rights reserved.
 **
 ** This file is part of the QxtGui module of the Qxt library.
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
#ifndef QXTWINDOWSYSTEM_H
#define QXTWINDOWSYSTEM_H

#include <QWidget>
#include "qxtglobal.h"

typedef QList<WId> WindowList;

class QXT_GUI_EXPORT QxtWindowSystem
{
public:
    static WindowList windows();
    static WId activeWindow();
    static WId findWindow(const QString& title);
    static WId windowAt(const QPoint& pos);
    static QString windowTitle(WId window);
    static QStringList windowTitles();
    static QRect windowGeometry(WId window);

    static uint idleTime();

    static QSize resolution(QWidget* screen = 0);
    static bool setResolution(int width, int height, QWidget* screen = 0);
    static bool setResolution(const QSize& resolution, QWidget* screen = 0);
    static QList<QSize> availableResolutions(QWidget* screen = 0);
};

#endif // QXTWINDOWSYSTEM_H
