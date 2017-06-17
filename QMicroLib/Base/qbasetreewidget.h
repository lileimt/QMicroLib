#ifndef QBASETREEWIDGET_H
#define QBASETREEWIDGET_H

#include <QTreeWidget>

class QBaseTreeWidget : public QTreeWidget
{
	Q_OBJECT

public:
	QBaseTreeWidget(QWidget *parent);
	~QBaseTreeWidget();

private:
	
};

#endif // QBASETREEWIDGET_H
