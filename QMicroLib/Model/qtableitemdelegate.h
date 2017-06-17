#ifndef QTABLEITEMDELEGATE_H
#define QTABLEITEMDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class QTableItemDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	QTableItemDelegate(QObject *parent = 0);
	~QTableItemDelegate();

private:
	
};

class QNoFocusDelegate : public QStyledItemDelegate
{
	Q_OBJECT;

public:
	QNoFocusDelegate(QObject *parent = 0);

protected:
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // QTABLEITEMDELEGATE_H
