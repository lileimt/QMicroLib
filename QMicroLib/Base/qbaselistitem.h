#ifndef QBASELISTITEM_H
#define QBASELISTITEM_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QPaintEvent>
#include "ui_baselistitem.h"

class QBaseListItem : public QWidget
{
	Q_OBJECT

public:
	QBaseListItem(QPixmap pixmap,QString strName,QWidget *parent = 0);
	~QBaseListItem();

	void setWidgetVisible(bool bVisible);
private:
	Ui::QBaseListItem ui;

protected:
	void paintEvent(QPaintEvent *event);
};

#endif // QBASELISTITEM_H
