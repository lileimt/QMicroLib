#ifndef QTOOLBARWIDGET_H
#define QTOOLBARWIDGET_H

#include "ui_toolbarwidget.h"
#include "Base/qbasewidget.h"

class QToolBarWidget : public QBaseWidget
{
	Q_OBJECT

public:
	QToolBarWidget(QWidget *parent = 0);
	~QToolBarWidget();

signals:
	void uploadClicked();
	void downloadClicked();
	void deleteClicked();
	void newFileClicked();
	void shareClicked();
	void moreClicked();
	void searchClicked(QString text);
	void sigTextChanged(const QString &text);
private:
	Ui::QToolBarWidget ui;
};

#endif // QTOOLBARWIDGET_H
