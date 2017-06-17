#ifndef QTABLETITLEBAR_H
#define QTABLETITLEBAR_H

#include "ui_tabletitlebarwidget.h"
#include "Base/qbasewidget.h"
#include <QHBoxLayout>
#include "qpathitem.h"
#include "Model/FileNode.h"

class QTableTitleBarWidget : public QBaseWidget
{
	Q_OBJECT

public:
	QTableTitleBarWidget(CFileNode *pNode,QWidget *parent = 0);
	~QTableTitleBarWidget();

	void addWidget(CFileNode *fileNode,bool bHome = false);
	void delWidget(int nIndex);

protected:
	bool eventFilter(QObject *watched, QEvent *event);

public slots:
	void slotRemovePathItem(int nIndex);
	void slotBack();
	void slotAddWidget(CFileNode *pNode);
signals:
	void sigBack(CFileNode *pNode);
private:
	Ui::QTableTitleBarWidget ui;
	QHBoxLayout *m_pLayout;

	QVector<QPathItem *> m_pathItems;
	int m_sumWidth;
	bool m_bListView;
	CFileNode *m_pNode;

	void clearPathItem();
};

#endif // QTABLETITLEBAR_H
