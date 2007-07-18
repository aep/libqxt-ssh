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
#include "qxttreewidgetitem.h"
#include "qxttreewidget.h"

/*!
    \class QxtTreeWidgetItem QxtTreeWidgetItem
    \ingroup gui
    \brief An extended QTreeWidgetItem.

    QxtTreeWidgetItem provides means for offering check state change signals and
    convenience methods for testing and setting flags.

    \sa QxtTreeWidget
 */


QxtTreeWidgetItem::QxtTreeWidgetItem(int type)
	: QTreeWidgetItem(type)
{
}

QxtTreeWidgetItem::QxtTreeWidgetItem(const QStringList& strings, int type)
	: QTreeWidgetItem(strings, type)
{
}

QxtTreeWidgetItem::QxtTreeWidgetItem(QTreeWidget* parent, int type)
	: QTreeWidgetItem(parent, type)
{
}

QxtTreeWidgetItem::QxtTreeWidgetItem(QTreeWidget* parent, const QStringList& strings, int type)
	: QTreeWidgetItem(parent, strings, type)
{
}

QxtTreeWidgetItem::QxtTreeWidgetItem(QTreeWidget* parent, QTreeWidgetItem* preceding, int type)
	: QTreeWidgetItem(parent, preceding, type)
{
}

QxtTreeWidgetItem::QxtTreeWidgetItem(QTreeWidgetItem* parent, int type)
	: QTreeWidgetItem(parent, type)
{
}

QxtTreeWidgetItem::QxtTreeWidgetItem(QTreeWidgetItem* parent, const QStringList& strings, int type)
	: QTreeWidgetItem(parent, strings, type)
{
}

QxtTreeWidgetItem::QxtTreeWidgetItem(QTreeWidgetItem* parent, QTreeWidgetItem* preceding, int type)
	: QTreeWidgetItem(parent, preceding, type)
{
}

QxtTreeWidgetItem::QxtTreeWidgetItem(const QxtTreeWidgetItem& other)
	: QTreeWidgetItem(other)
{
}

QxtTreeWidgetItem::~QxtTreeWidgetItem()
{
}

/*!
    Returns \b true if the \a flag is set, otherwise \b false.

    \sa setFlag(), QTreeWidgetItem::flags(), Qt::ItemFlag
 */
bool QxtTreeWidgetItem::testFlag(Qt::ItemFlag flag) const
{
	return (flags() & flag);
}

/*!
    If \a enabled is \b true, the item \a flag is enabled; otherwise, it is disabled.

    \sa testFlag(), QTreeWidgetItem::setFlags(), Qt::ItemFlag
 */
void QxtTreeWidgetItem::setFlag(Qt::ItemFlag flag, bool enabled)
{
	if (enabled)
		setFlags(flags() | flag);
	else
		setFlags(flags() & ~flag);
}

void QxtTreeWidgetItem::setData(int column, int role, const QVariant& value)
{
	if (role == Qt::CheckStateRole)
	{
		const Qt::CheckState newState = static_cast<Qt::CheckState>(value.toInt());
		const Qt::CheckState oldState = static_cast<Qt::CheckState>(data(column, role).toInt());
		
		QTreeWidgetItem::setData(column, role, value);
		
		if (newState != oldState)
		{
			QxtTreeWidget* tree = qobject_cast<QxtTreeWidget*>(treeWidget());
			if (tree)
			{
				emit tree->itemCheckStateChanged(this);
			}
		}
	}
	else
	{
		QTreeWidgetItem::setData(column, role, value);
	}
}