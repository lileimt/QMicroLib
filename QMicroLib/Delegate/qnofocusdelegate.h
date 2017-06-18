#ifndef QNOFOCUSDELEGATE_H
#define QNOFOCUSDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class QNoFocusDelegate : public QStyledItemDelegate
{
	Q_OBJECT;

public:
	QNoFocusDelegate(QObject *parent = 0);

protected:
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // QNOFOCUSDELEGATE_H
