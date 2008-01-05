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
#ifndef QXTBASESPINBOX_H
#define QXTBASESPINBOX_H

#include <QSpinBox>
#include "qxtglobal.h"
#include "qxtpimpl.h"

class QxtBaseSpinBoxPrivate;

class QXT_GUI_EXPORT QxtBaseSpinBox : public QSpinBox
{
    Q_OBJECT
    QXT_DECLARE_PRIVATE(QxtBaseSpinBox);
    Q_PROPERTY(int base READ base WRITE setBase)
    Q_PROPERTY(bool upperCase READ isUpperCase WRITE setUpperCase)

public:
    explicit QxtBaseSpinBox(QWidget* parent = 0);
    explicit QxtBaseSpinBox(int base, QWidget* parent = 0);
    virtual ~QxtBaseSpinBox();

    virtual void fixup(QString& input) const;
    virtual QValidator::State validate(QString& input, int& pos) const;

    bool isUpperCase() const;
    void setUpperCase(bool upperCase);

    int base() const;

public slots:
    void setBase(int base);

signals:
    void baseChanged(int base);

protected:
    virtual QString textFromValue(int value) const;
    virtual int valueFromText(const QString& text) const;
};

#endif // QXTBASESPINBOX_H
