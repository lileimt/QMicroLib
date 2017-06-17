#ifndef QBASETABLEWIDGET_H
#define QBASETABLEWIDGET_H

#include <QTableWidget>
#include <QStyledItemDelegate>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QList>
#include <QColor>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QMouseEvent>
#include "Common/struct.h"

typedef struct {
	int previousRow;
	QColor previousColor;
}PREVIOUS_STATUS;

//class QNoFocusDelegate : public QStyledItemDelegate
//{
//	Q_OBJECT;
//
//public:
//	QNoFocusDelegate(QObject *parent = 0);
//
//protected:
//	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
//};

class QBaseTableWidget : public QTableWidget
{
	Q_OBJECT

public:
	QBaseTableWidget(QWidget *parent = 0);
	~QBaseTableWidget();

	void setHorizontalHeader(QStringList header);
	void insertTableItem();

	void setFileInfo(QList<FILE_INFO> fileInfo);
	void setCheckBoxStatus(int state);
	int getRowCount();
	void checkBoxSelectedCountIncrease();
	void checkBoxSelectedCountDecrease();

	void clearAllRows();
protected:
	void contextMenuEvent(QContextMenuEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
public slots:
	void slotSortByColumn(int column);
	void slotCellEntered(int row, int column);
	void slotCellClicked(int row, int column);
	void slotCellDoubleClicked(int row, int column);
	void slotSectionEntered(int logicalIndex);
private:
	QList<FILE_INFO> m_fileInfo;
	QCheckBox *m_chkBox;
	QColor m_defaultBkColor;
	QColor m_selectedBkColor;
	QColor m_hoverBkColor;
	QColor m_selectedBorderColor;
	QColor m_hoverBorderColor;
	//int m_previousColorRow;
	PREVIOUS_STATUS m_previousStatus;
	QMenu *m_popMenu;
	QAction *m_openAction;
	QAction *m_renameAction;
	QAction *m_downloadAction;
	QAction *m_uploadAction;
	QAction *m_createFolderAction;
	QAction *m_flushAction;
	QAction *m_deleteAction;
	bool m_bRename;
	QTableWidgetItem *m_renameItem;
	int m_iCheckBoxSelectedCount;

	void setRowColor(int row, QColor color);
	void createAction();
	int getCheckBoxSelectedCount();
};

#endif // QBASETABLEWIDGET_H
