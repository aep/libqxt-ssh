/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtDesigner module of the Qxt library.
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

#ifndef QXTCOUNTRYMODEL_H
#define QXTCOUNTRYMODEL_H
#include <QAbstractTableModel>
#include "qxtglobal.h"
#include "qxtpimpl.h"

class QxtCountryModelPrivate;

class QXT_GUI_EXPORT QxtCountryModel : public QAbstractTableModel
{
    Q_OBJECT
  public:
    QXT_DECLARE_PRIVATE(QxtCountryModel);

  public:
    explicit QxtCountryModel(QObject* parent = 0);
    ~QxtCountryModel();

    int rowCount(const QModelIndex&) const;
    int columnCount(const QModelIndex&) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
};

#endif  //QXTCOUNTRYMODEL_H
