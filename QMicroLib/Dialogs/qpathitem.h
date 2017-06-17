#ifndef QPATHITEM_H
#define QPATHITEM_H

#include "Base/qbasewidget.h"
#include "ui_pathitem.h"
#include "Model/FileNode.h"

class QPathItem : public QBaseWidget
{
	Q_OBJECT

public:
	QPathItem(CFileNode *FileNode,bool bHome = false, QWidget *parent = 0);
	~QPathItem();

	int getWidth();
	void setIndex(int index);
	int getIndex();
	CFileNode *getCurNode();
signals:
	void sigClicked(int index);
protected:
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);
	bool eventFilter(QObject *watched, QEvent *event);
private:
	Ui::QPathItem ui;
	QString m_strPath;
	//bool m_hasChildDirs;
	bool m_bHome;

	CFileNode *m_FileNode;
	int m_index;   //记录当前窗口在标题栏显示的索引
};

#endif // QPATHITEM_H
