#ifndef QBASEWIDGET_H
#define QBASEWIDGET_H

#include <QWidget>
#include "ui_basewidget.h"

class QBaseWidget : public QWidget
{
	Q_OBJECT

public:
	QBaseWidget(QWidget *parent = 0);
	~QBaseWidget();

protected:
	void paintEvent(QPaintEvent *);

private:
	Ui::QBaseWidget ui;
};

#endif // QBASEWIDGET_H
