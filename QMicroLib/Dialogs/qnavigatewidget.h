#ifndef QNAVIGATEWIDGET_H
#define QNAVIGATEWIDGET_H

#include "Base/qbasewidget.h"
#include "ui_navigatewidget.h"

class QNavigateWidget : public QBaseWidget
{
	Q_OBJECT

public:
	QNavigateWidget(QWidget *parent = 0);
	~QNavigateWidget();

signals:
	void sigAllFiles();
	void sigWord();
	void sigExcel();
	void sigPPT();
	void sigImage();
	void sigMovie();
	void sigOther();
	void sigRecvFiles();
	void sigFolder();
	void sigMyCollect();
	void sigMyCommit();
	void sigHistory();
	void sigRecycelBin();
private:
	Ui::QNavigateWidget ui;
};

#endif // QNAVIGATEWIDGET_H
