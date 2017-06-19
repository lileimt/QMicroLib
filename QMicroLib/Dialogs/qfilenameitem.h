#ifndef QFILENAMEITEM_H
#define QFILENAMEITEM_H

#include <QWidget>
#include <QLineEdit>
#include <QPixmap>
#include <QPainter>
#include <QPalette>
#include <QPaintEvent>
#include "ui_filenameitem.h"
#include "Base/qbasefileicon.h"
//#include "Base/qbasetablewidget.h"
//#include "Base/qbasetableview.h"
#include "Model/FileNode.h"

class QFileNameItem : public QWidget
{
	Q_OBJECT

public:
	QFileNameItem(CFileNode *node,QWidget *parent = 0);
	~QFileNameItem();

	void showFileNameEdit();
private:
	Ui::QFileNameItem ui;
	CFileNode *m_fileNode;
	//bool m_bDir;
	//QString m_fileName;
	QIcon m_icon;
	//QBaseTableWidget *m_parentWidget;
	//QBaseTableView *m_parentWidget;

	void hideFileNameEdit();
	void setFileName(QString fileName);
protected:
	//void paintEvent(QPaintEvent *event);
	bool eventFilter(QObject *watched, QEvent *event);
signals :
	void sigSetChecked();
	void sigChangeDir(CFileNode *pNode);

public:
	QLineEdit *m_lineEdit;
	QCheckBox *m_checkBox;

	void setToolButtonVisible(bool bShow);
	void setBackgroundColor(QColor color);
};

#endif // QFILENAMEITEM_H
