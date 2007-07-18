/****************************************************************************
**
** Copyright (C) J-P Nurmi <jpnurmi@gmail.com>. Some rights reserved.
**
** This file is part of the QxtGui module of the
** Qt eXTension library <http://libqxt.sourceforge.net>
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "qxtdesktopwidget.h"
#include <QStringList>

/*!
    \class QxtDesktopWidget QxtDesktopWidget
    \ingroup gui
    \brief QxtDesktopWidget provides means for accessing native windows.

    \note QxtDesktopWidget is portable in principle, but be careful while
    using it since you are probably about to do something non-portable.

    <P>Advanced example usage:
    \code
    class NativeWindow : public QWidget {
        public:
            NativeWindow(WId wid) {
                QWidget::create(wid, false, false); // window, initializeWindow, destroyOldWindow
            }
            ~NativeWindow() {
                QWidget::destroy(false, false); // destroyWindow, destroySubWindows
            }
    };
    \endcode

    \code
    WindowList windows = QxtDesktopWidget::windows();
    QStringList titles = QxtDesktopWidget::windowTitles();
    bool ok = false;
    QString title = QInputDialog::getItem(0, "Choose Window", "Choose a window to be hid:", titles, 0, false, &ok);
    if (ok)
    {
        int index = titles.indexOf(title);
        if (index != -1)
        {
            NativeWindow window(windows.at(index));
            window.hide();
        }
    }
    \endcode

    \note Currently supported platforms are \b X11 and \b Windows.
 */

/*!
    \fn QxtDesktopWidget::windows()

    Returns the list of native window system identifiers.

    \note The windows are not necessarily QWidgets.

    \sa QApplication::topLevelWidgets(), windowTitles()
 */


/*!
    \fn QxtDesktopWidget::activeWindow()

    Returns the native window system identifier of the active window if any.

    Example usage:
    \code
    WId wid = QxtDesktopWidget::activeWindow();
    QString title = QxtDesktopWidget::windowTitle(wid);
    qDebug() << "Currently active window is:" << title;
    \endcode

    \note The window is not necessarily a QWidget.

    \sa QApplication::activeWindow()
 */

/*!
    \fn QxtDesktopWidget::findWindow(const QString& title)

    Returns the native window system identifier of the window if any with given \a title.

    Example usage:
    \code
    WId wid = QxtDesktopWidget::findWindow("Mail - Kontact");
    QPixmap screenshot = QPixmap::grabWindow(wid);
    \endcode

    \note The window is not necessarily a QWidget.

    \sa QWidget::find()
 */

/*!
    \fn QxtDesktopWidget::windowAt(const QPoint& pos)

    Returns the native window system identifier of the window if any at \a pos.

    Example usage:
    \code
    QPoint point = // a mouse press or something
    WId wid = QxtDesktopWidget::windowAt(point);
    QPixmap screenshot = QPixmap::grabWindow(wid);
    \endcode

    \note The window is not necessarily a QWidget.

    \sa QApplication::widgetAt()
 */

/*!
    \fn QxtDesktopWidget::windowTitle(WId window)

    Returns the title of the native \a window.

    Example usage:
    \code
    WId wid = QxtDesktopWidget::activeWindow();
    QString title = QxtDesktopWidget::windowTitle(wid);
    qDebug() << "Currently active window is:" << title;
    \endcode

    \sa QWidget::windowTitle(), windowTitles()
 */

/*!
    \fn QxtDesktopWidget::windowTitles()

    Returns a list of native window titles.

    Example usage:
    \code
    qDebug() << "Windows:";
    foreach (QString title, QxtDesktopWidget::windowTitles())
       qDebug() << title;
    \endcode

    \sa QWidget::windowTitle(), windowTitle(), windows()
 */

/*!
    \fn QxtDesktopWidget::windowGeometry(WId window)

    Returns the geometry of the native \a window.

    Example usage:
    \code
    WId wid = QxtDesktopWidget::activeWindow();
    QRect geometry = QxtDesktopWidget::windowGeometry(wid);
    qDebug() << "Geometry of the active window is:" << geometry;
    \endcode

    \sa QWidget::frameGeometry()
 */

QStringList QxtDesktopWidget::windowTitles()
{
	WindowList windows = QxtDesktopWidget::windows();
	QStringList titles;
	foreach (WId window, windows)
		titles += QxtDesktopWidget::windowTitle(window);
	return titles;
}