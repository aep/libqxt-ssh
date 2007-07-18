/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** There is aditional information in the LICENSE file of libqxt.
** If you did not receive a copy of the file try to download it or
** contact the libqxt Management
** 
** <http://libqxt.sourceforge.net>  <aep@exys.org>  <coda@bobandgeorge.com>
**
****************************************************************************/


#ifndef QXTAPPLICATION_H
#define QXTAPPLICATION_H

#include <QPair>
#include <QList>
#include <QMultiHash>
#include <QApplication>
#include "qxtglobal.h"

typedef QPair<uint, uint> Identifier;
typedef QList<Identifier> Identifiers;
typedef QPair<QWidget*, const char*> Receiver;
typedef QList<Receiver> Receivers;

#define qxtApp (QxtApplication::instance())

class QXT_GUI_EXPORT QxtApplication : public QApplication
{
public:
	QxtApplication(int& argc, char** argv);
	QxtApplication(int& argc, char** argv, bool GUIenabled);
	QxtApplication(int& argc, char** argv, Type type);
#if defined(Q_WS_X11)
	QxtApplication(Display* display, Qt::HANDLE visual = 0, Qt::HANDLE colormap = 0);
	QxtApplication(Display* display, int& argc, char** argv, Qt::HANDLE visual = 0, Qt::HANDLE colormap = 0);
#endif // Q_WS_X11
	virtual ~QxtApplication();
		
#ifndef QXT_DOXYGEN_RUN
#if defined(Q_WS_X11)
	virtual bool x11EventFilter(XEvent* event);
#elif defined(Q_WS_WIN)
	virtual bool winEventFilter(MSG* msg, long* result);
#elif defined(Q_WS_MAC)
    virtual bool macEventFilter(EventHandlerCallRef caller, EventRef event);
#endif // Q_WS_WIN
#endif // QXT_DOXYGEN_RUN
	
	bool addHotKey(Qt::KeyboardModifiers modifiers, Qt::Key key, QWidget* receiver, const char* member);
	bool removeHotKey(Qt::KeyboardModifiers modifiers, Qt::Key key, QWidget* receiver, const char* member);
	
	inline static QxtApplication* instance() { return static_cast<QxtApplication*>(QApplication::instance()); }
	
#ifndef QXT_DOXYGEN_RUN
protected:
	virtual uint nativeKeycode(Qt::Key key) const;
	virtual uint nativeModifiers(Qt::KeyboardModifiers modifiers) const;

private:
	bool registerHotKey(uint modifiers, uint keycode, QWidget* receiver);
	bool unregisterHotKey(uint modifiers, uint keycode, QWidget* receiver);
	void activateHotKey(uint modifiers, uint keycode) const;
	
	QMultiHash<Identifier, Receiver> hotkeys;
#endif // QXT_DOXYGEN_RUN
};

inline uint qHash(const QPair<uint, uint>& value)
{
	return qHash(value.first) ^ qHash(value.second);
}

#endif // QXTAPPLICATION_H