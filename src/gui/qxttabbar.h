/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtGui module of the Qxt library
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
** <http://libqxt.org>  <foundation@libqxt.org>
**
****************************************************************************/
#ifndef QXTTABBAR_H
#define QXTTABBAR_H

#include <QTabBar>
#include "qxtnamespace.h"
#include "qxtglobal.h"
#include "qxtpimpl.h"

class QxtTabBarPrivate;
class QXT_GUI_EXPORT QxtTabBar : public QTabBar
{
    Q_OBJECT
    QXT_DECLARE_PRIVATE(QxtTabBar)
    Q_PROPERTY(TabMovementMode tabMovementMode READ tabMovementMode WRITE setTabMovementMode)

public:
    explicit QxtTabBar(QWidget* parent = 0);
    virtual ~QxtTabBar();

    enum TabMovementMode
    {
        NoMovement,
        InPlaceMovement,
        DragDropMovement
    };

    TabMovementMode tabMovementMode() const;
    void setTabMovementMode(TabMovementMode mode);

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dropEvent(QDropEvent* event);

signals:
    void tabMoved(int fromIndex, int toIndex);
};

#endif // QXTTABBAR_H
