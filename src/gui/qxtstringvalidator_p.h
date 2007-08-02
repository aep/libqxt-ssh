/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
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
** <http://libqxt.sourceforge.net>  <libqxt@gmail.com>
**
****************************************************************************/
#ifndef QXTSTRINGLISTVALIDATOR_P_H_INCLUDED
#define QXTSTRINGLISTVALIDATOR_P_H_INCLUDED

#include <QxtPimpl>
#include <QStringList>
#include <QModelIndex>
#include <QPointer>

class QxtStringValidator;

class QxtStringValidatorPrivate : public QxtPrivate<QxtStringValidator>
{
    public:
        QxtStringValidatorPrivate();
        QXT_DECLARE_PUBLIC(QxtStringValidator);

        bool isUserModel;
        QPointer<QAbstractItemModel> model;
        Qt::CaseSensitivity cs;
        int lookupColumn;
        int lookupRole;
        Qt::MatchFlags userFlags;
        QModelIndex lookupStartModelIndex;

        QModelIndex lookupPartialMatch(const QString &value) const;
        QModelIndex lookupExactMatch(const QString &value) const;
        QModelIndex lookup(const QString &value,const Qt::MatchFlags  &matchFlags) const;
        
};

#endif //QXTSTRINGLISTVALIDATOR_P_H_INCLUDED