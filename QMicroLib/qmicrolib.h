#ifndef QMICROLIB_H
#define QMICROLIB_H

#include <QtWidgets/QDialog>
#include "ui_microlib.h"
#include <QList>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "Common/struct.h"
#include "Dialogs/qtoolbarwidget.h"
#include "Dialogs/qtabletitlebarwidget.h"
#include "Dialogs/qnavigatewidget.h"
#include "Base/qbasetableview.h"
#include "Model/qtablemodel.h"
#include "Dialogs/qfilenameitem.h"

class QMicroLib : public QDialog
{
	Q_OBJECT

public:
	QMicroLib(QWidget *parent = 0);
	~QMicroLib();

public slots:
	
private:
	Ui::QMicroLibClass ui;
	//QBaseTableWidget *m_tableWidget;
	//QBaseListWidget *m_listWidget;
	QNavigateWidget *m_navWidget;
	QToolBarWidget *m_toolBarWidget;
	QTableTitleBarWidget *m_titleBarWidget;
	QBaseTableView *m_tableView;
	QHBoxLayout *m_pLayout;
	QVBoxLayout *m_rightVBoxLayout;
};

#endif // QMICROLIB_H
