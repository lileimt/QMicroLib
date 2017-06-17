#ifndef QWIDGETDELEGATE_H
#define QWIDGETDELEGATE_H

#include <QItemDelegate>
#include "Dialogs/qfilenameitem.h"

class QWidgetDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	QWidgetDelegate(QObject *parent = 0);
	~QWidgetDelegate();

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:

};

#endif // QWIDGETDELEGATE_H
