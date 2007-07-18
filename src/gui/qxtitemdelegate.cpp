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
#include "qxtitemdelegate.h"
#include "qxtitemdelegate_p.h"
#include <QApplication>
#include <QTreeView>
#include <QPainter>

static const int TOP_LEVEL_EXTENT = 2;

QxtItemDelegatePrivate::QxtItemDelegatePrivate() :
	textVisible(true),
	progressFormat("%1%"),
	elide(Qt::ElideMiddle),
	style(Qxt::NoDecoration)
{
}

void QxtItemDelegatePrivate::paintButton(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index, const QTreeView* view) const
{
	// draw the button
	QStyleOptionButton buttonOption;
	buttonOption.state = option.state;
#ifdef Q_WS_MAC
	buttonOption.state |= QStyle::State_Raised;
#endif
	buttonOption.state &= ~QStyle::State_HasFocus;
	if (view->isExpanded(index))
		buttonOption.state |= QStyle::State_Sunken;
	buttonOption.rect = option.rect;
	buttonOption.palette = option.palette;
	buttonOption.features = QStyleOptionButton::None;
	view->style()->drawControl(QStyle::CE_PushButton, &buttonOption, painter, view);

	// draw the branch indicator
	static const int i = 9;
	const QRect& r = option.rect;
	if (index.model()->hasChildren(index))
	{
		QStyleOption branchOption;
		branchOption.initFrom(view);
		if (branchOption.direction == Qt::LeftToRight)
			branchOption.rect = QRect(r.left() + i/2, r.top() + (r.height() - i)/2, i, i);
		else
			branchOption.rect = QRect(r.right() - i/2 - i, r.top() + (r.height() - i)/2, i, i);
		branchOption.palette = option.palette;
		branchOption.state = QStyle::State_Children;
		if (view->isExpanded(index))
			branchOption.state |= QStyle::State_Open;
		view->style()->drawPrimitive(QStyle::PE_IndicatorBranch, &branchOption, painter, view);
	}

	// draw the text
	QRect textrect = QRect(r.left() + i*2, r.top(), r.width() - ((5*i)/2), r.height());
#if QT_VERSION < 0x040200
	QString text = QItemDelegate::elidedText(option.fontMetrics, textrect.width(), elide, index.data().toString());
#else // QT_VERSION >= 0x040200
	QString text = option.fontMetrics.elidedText(index.data().toString(), elide, textrect.width());
#endif // QT_VERSION
	view->style()->drawItemText(painter, textrect, Qt::AlignCenter, option.palette, view->isEnabled(), text);
}

void QxtItemDelegatePrivate::paintMenu(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index, const QTreeView* view) const
{
	// draw the menu bar item
	QStyleOptionMenuItem menuOption;
	menuOption.palette = view->palette();
	menuOption.fontMetrics = view->fontMetrics();
	menuOption.state = QStyle::State_None;
	// QModelIndex::flags() was introduced in 4.2
        // => therefore "index.model()->flags(index)"
	if (view->isEnabled() && index.model()->flags(index) & Qt::ItemIsEnabled)
		menuOption.state |= QStyle::State_Enabled;
	else
		menuOption.palette.setCurrentColorGroup(QPalette::Disabled);
	menuOption.state |= QStyle::State_Selected;
	menuOption.state |= QStyle::State_Sunken;
	menuOption.state |= QStyle::State_HasFocus;
	menuOption.rect = option.rect;
	menuOption.text = index.data().toString();
	menuOption.icon = QIcon(index.data(Qt::DecorationRole).value<QPixmap>());
	view->style()->drawControl(QStyle::CE_MenuBarItem, &menuOption, painter, view);
	
	// draw the an arrow as a branch indicator
	if (index.model()->hasChildren(index))
	{
		QStyle::PrimitiveElement arrow;
		if (view->isExpanded(index))
			arrow = QStyle::PE_IndicatorArrowUp;
		else
			arrow = QStyle::PE_IndicatorArrowDown;
		static const int i = 9;
		const QRect& r = option.rect;
		menuOption.rect = QRect(r.left() + i/2, r.top() + (r.height() - i)/2, i, i);
		view->style()->drawPrimitive(arrow, &menuOption, painter, view);
	}
}

void QxtItemDelegatePrivate::paintProgress(QPainter* painter, const QStyleOptionViewItem& option, int progress) const
{
	QStyleOptionProgressBar opt;
	opt.minimum = 0;
	opt.maximum = 100;
	opt.rect = option.rect;
	opt.progress = progress;
	opt.textVisible = textVisible;
	opt.text = progressFormat.arg(progress);
	QApplication::style()->drawControl(QStyle::CE_ProgressBar, &opt, painter, 0);
}

void QxtItemDelegatePrivate::setCurrentEditor(QWidget* editor, const QModelIndex& index) const
{
	currentEditor = editor;
	currentEdited = index;
}

void QxtItemDelegatePrivate::closeEditor(QWidget* editor)
{
	if (currentEdited.isValid() && editor == currentEditor)
	{
		setCurrentEditor(0, QModelIndex());
		emit qxt_p().editingFinished(currentEdited);
	}
}

/*!
    \class QxtItemDelegate QxtItemDelegate
    \ingroup gui
    \brief An extended QItemDelegate with additional signals and optional decoration.

    QxtItemDelegate provides signals for starting and finishing of editing
    and an optional decoration for top level indices in a QTreeView.
    QxtItemDelegate can also draw a progress bar for indices providing
    appropriate progress data. 
 */

/*!
    \fn QxtItemDelegate::editingStarted(const QModelIndex& index)

    This signal is emitted after the editing of \a index has been started.

    \sa editingFinished()
 */

/*!
    \fn QxtItemDelegate::editingFinished(const QModelIndex& index)

    This signal is emitted after the editing of \a index has been finished.

    \sa editingStarted()
 */

/*!
    Constructs a new QxtItemDelegate with \a parent.
 */
QxtItemDelegate::QxtItemDelegate(QObject* parent) : QItemDelegate(parent)
{
	QXT_INIT_PRIVATE(QxtItemDelegate);
	connect(this, SIGNAL(closeEditor(QWidget*)), &qxt_d(), SLOT(closeEditor(QWidget*)));
}

/*!
    Destructs the item delegate.
 */
QxtItemDelegate::~QxtItemDelegate()
{
}

/*!
    \property QxtItemDelegate::decorationStyle
    \brief This property holds the top level index decoration style

    Top level indices are decorated according to this property.
    The default value is \b Qxt::NoDecoration.

    \note The property has effect only in case the delegate is installed
    on a QTreeView. The view must be the parent of the delegate.

    \note Set \b QTreeView::rootIsDecorated to \b false to avoid
    multiple branch indicators.

    \sa Qxt::DecorationStyle, QTreeView::rootIsDecorated
 */
Qxt::DecorationStyle QxtItemDelegate::decorationStyle() const
{
	return qxt_d().style;
}

void QxtItemDelegate::setDecorationStyle(Qxt::DecorationStyle style)
{
	qxt_d().style = style;
}

/*!
    \property QxtItemDelegate::elideMode
    \brief This property holds the text elide mode

    The text of a decorated top level index is elided according to this property.
    The default value is \b Qt::ElideMiddle.

    \note The property has effect only for decorated top level indices.

    \sa decorationStyle, Qt::TextElideMode
 */
Qt::TextElideMode QxtItemDelegate::elideMode() const
{
	return qxt_d().elide;
}

void QxtItemDelegate::setElideMode(Qt::TextElideMode mode)
{
	qxt_d().elide = mode;
}

/*!
    \property QxtItemDelegate::progressTextFormat
    \brief This property holds the format of optional progress text

    The progress text is formatted according to this property.
    The default value is \b "%1%".

    \note Progress bar is rendered for indices providing valid
    numerical data for \b ProgressRole.
	
	\note \b \%1 is replaced by the progress percent.

    \sa progressTextVisible, ProgressRole
 */
QString QxtItemDelegate::progressTextFormat() const
{
	return qxt_d().progressFormat;
}

void QxtItemDelegate::setProgressTextFormat(const QString& format)
{
	qxt_d().progressFormat = format;
}

/*!
    \property QxtItemDelegate::progressTextVisible
    \brief This property holds whether progress text is visible

    The default value is \b true.
    
    \note Progress bar is rendered for indices providing valid
    numerical data for \b ProgressRole.

    \sa progressTextFormat, ProgressRole
 */
bool QxtItemDelegate::isProgressTextVisible() const
{
	return qxt_d().textVisible;
}

void QxtItemDelegate::setProgressTextVisible(bool visible)
{
	qxt_d().textVisible = visible;
}

QWidget* QxtItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QWidget* editor = QItemDelegate::createEditor(parent, option, index);
	qxt_d().setCurrentEditor(editor, index);
	emit const_cast<QxtItemDelegate*>(this)->editingStarted(index);
	return editor;
}

void QxtItemDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	QItemDelegate::setModelData(editor, model, index);
	qxt_d().setCurrentEditor(0, QModelIndex());
	emit const_cast<QxtItemDelegate*>(this)->editingFinished(index);
}

void QxtItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	const QAbstractItemModel* model = index.model();
	const QTreeView* tree = dynamic_cast<QTreeView*>(parent());
	const bool topLevel = !index.parent().isValid();
	
	if (tree && model && topLevel && qxt_d().style != Qxt::NoDecoration)
	{
		QStyleOptionViewItem opt;
		opt.QStyleOption::operator=(option);
		opt.showDecorationSelected = false;

		QModelIndex valid = model->index(index.row(), 0);
		QModelIndex sibling = valid;
		while (sibling.isValid())
		{
			opt.rect |= tree->visualRect(sibling);
			sibling = sibling.sibling(sibling.row(), sibling.column() + 1);
		}

		switch (qxt_d().style)
		{
			case Qxt::Buttonlike:
				qxt_d().paintButton(painter, opt, valid, tree);
				break;
			case Qxt::Menulike:
				qxt_d().paintMenu(painter, opt, valid, tree);
				break;
			default:
				qWarning("QxtItemDelegate::paint() unknown decoration style");
				QItemDelegate::paint(painter, opt, valid);
				break;
		}
	}
	else
	{
		QItemDelegate::paint(painter, option, index);

		bool ok = false;
		const QVariant data = index.data(ProgressRole);
		const int progress  = data.toInt(&ok);
		if (data.isValid() && ok)
			qxt_d().paintProgress(painter, option, progress);
	}
}

QSize QxtItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	// something slightly bigger for top level indices
	QSize size = QItemDelegate::sizeHint(option, index);
	if (!index.parent().isValid())
		size += QSize(TOP_LEVEL_EXTENT, TOP_LEVEL_EXTENT);
	return  size;
}