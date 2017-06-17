#ifndef QBASELISTWIDGET_H
#define QBASELISTWIDGET_H

#include <QListWidget>

const int iconWidth = 110;
const int iconHeight = 100;

class QBaseListWidget : public QListWidget
{
	Q_OBJECT

public:
	QBaseListWidget(QWidget *parent = 0);
	~QBaseListWidget();

	void addItemIntoListWidget(QPixmap pixmap, QString text);
private:
	
};

#endif // QBASELISTWIDGET_H
