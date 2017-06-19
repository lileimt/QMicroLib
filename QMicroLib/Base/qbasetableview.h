#ifndef QBASETABLEVIEW_H
#define QBASETABLEVIEW_H

#include <QList>
#include <QMenu>
#include <QAction>
#include <QTableView>
#include <QMouseEvent>
#include "qbaseheaderview.h"
#include "Common/common.h"
#include "Model/FileNode.h"
#include "Model/qtablemodel.h"
#include "Model/qsortfiltermodel.h"

class QFileNameItem;

class QBaseTableView : public QTableView
{
	Q_OBJECT

public:
	QBaseTableView(QWidget *parent = 0);
	~QBaseTableView();

	void initHeaderView(QStringList header);
	QFileNameItem *getWidget(int row);
	QTableModel *getTableModel();
	void setModelData(QList<CFileNode *> *childNodes);
	void showTable(QList<CFileNode *> *childNodes);
	void addIndexWidget(QModelIndex index, CFileNode *pNode);
	void setCheckBoxState();
	void updateFirstColumn();
	void setAllRowsSelect();
protected:
	void mouseMoveEvent(QMouseEvent *event);
	void leaveEvent(QEvent *event);
public slots :
	void slotDeleteRow();
	void slotAddRow();
	void slotCheckBoxStateChanged(bool bChecked);
	void slotFilter(QString text);
	void slotEmptyFilter(const QString &text);

	void slotShowAllFiles();
	void slotShowWordFiles();
	void slotShowExcelFiles();
	void slotShowPPTFiles();
	void slotShowImageFiles();
	void slotShowMovieFiles();
	void slotShowOtherFiles();
	void slotChangeDir(CFileNode *pNode);
	void slotBackDir(CFileNode *pNode);

	void slotContextMenu(QPoint point);
signals:
	void sigChangeDir(CFileNode *pNode);

private:
	QBaseHeaderView *m_pHeaderView;
	QTableModel *m_pModel;
	QSortFilterModel *m_pSortMode;
	//QMap<QString, QFileNameItem*> m_pMap;
	QList<QFileNameItem *> m_pList;
	//CFileNode *m_fileNode;
	QList<CFileNode *> *m_childNodes;
	QList<CFileNode *> m_filterNodes;
	int m_curRow;
	int m_iCheckBoxSelectedCount;
	QMenu *m_popMenu;
	QMenu *m_popEmptyMenu;
	QAction *m_openAction;
	QAction *m_downloadAction;
	QAction *m_shareAction;
	QAction *m_uploadAction;
	QAction *m_newDirAction;
	QAction *m_renameAction;
	QAction *m_deleteAction;
	QAction *m_attributeAction;

	void updateRow(int row);
	void resetRow();
	void deleteWidget();
	void filterFileNodes(QString strText);
	void getAllFilesByType(QList<CFileNode *> *childNodes, QString strText);
	void createAction();
	void createEmptyAction();
	void renameAction(int row);
};

#endif // QBASETABLEVIEW_H
