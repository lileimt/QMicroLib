#include "qbasetablewidget.h"
#include "qbasefileicon.h"
#include <QDebug>
#include "Dialogs/qfilenameitem.h"

//QNoFocusDelegate::QNoFocusDelegate(QObject *parent)
//	:QStyledItemDelegate(parent)
//{
//
//}
//
//void QNoFocusDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//	QStyleOptionViewItem itemOption(option);
//	if (itemOption.state & QStyle::State_HasFocus){
//		itemOption.state = itemOption.state ^ QStyle::State_HasFocus;
//	}
//	QStyledItemDelegate::paint(painter, itemOption, index);
//}

QBaseTableWidget::QBaseTableWidget(QWidget *parent)
	: QTableWidget(parent),
	m_defaultBkColor(QColor(255, 255, 255)),
	m_selectedBkColor(QColor(205,226,252)),
	m_hoverBkColor(QColor(242,247,253)),
	m_selectedBorderColor(QColor(125,162,206)),
	m_hoverBorderColor(QColor(184,214,251)),
	//m_previousColorRow(-1),
	m_bRename(false),
	m_renameItem(nullptr),
	m_iCheckBoxSelectedCount(0)
{
	setWindowTitle(QString("tablewidget"));
	setFrameShape(QFrame::NoFrame);//设置无边框
	setShowGrid(false);//设置不显示格子线
	//setItemDelegate(new QNoFocusDelegate);   //去掉鼠标点击的虚框
	setSelectionMode(QAbstractItemView::ExtendedSelection);//可多选（Ctrl、Shrift、Ctrl+A都可以）
	setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为时每次选择一行
	//setSelectionMode(QAbstractItemView::SingleSelection);
	setEditTriggers(QAbstractItemView::NoEditTriggers);

	QHeaderView *headerView = horizontalHeader();
	headerView->setDefaultSectionSize(150);
	headerView->setDefaultAlignment(Qt::AlignLeft);
	headerView->setHighlightSections(false);//当表格只有一行的时候，则表头会出现塌陷问题，点击表时不对表头行光亮（获取焦点） 
	headerView->setFixedHeight(25);
	headerView->setStretchLastSection(true);

	connect(headerView, &QHeaderView::sectionClicked, this, &QBaseTableWidget::slotSortByColumn);
	connect(headerView, &QHeaderView::sectionEntered, this, &QBaseTableWidget::slotSectionEntered);

	headerView->setSortIndicator(0, Qt::AscendingOrder);
	headerView->setSortIndicator(1, Qt::AscendingOrder);
	headerView->setSortIndicator(2, Qt::AscendingOrder);
	headerView->setSortIndicatorShown(true);
	headerView->setSectionsClickable(true);

	QHeaderView *verticalHeaderView = verticalHeader();
	verticalHeaderView->setDefaultSectionSize(25);
	verticalHeaderView->setVisible(false);//设置垂直头不可见
	setMouseTracking(true);

	m_previousStatus.previousRow = -1;
	m_previousStatus.previousColor = m_defaultBkColor;

	m_chkBox = new QCheckBox(this);
	m_chkBox->setGeometry(9, 5, 16, 16);
	m_chkBox->setStyleSheet("QCheckBox{background:transparent;}");
	connect(m_chkBox, &QCheckBox::clicked, [=](){ 
		Qt::CheckState state = Qt::Checked;
		int rowCount = this->rowCount();
		if (m_chkBox->isChecked()){
			state = Qt::Checked;
			m_iCheckBoxSelectedCount = rowCount;
		}else{
			state = Qt::Unchecked;
			m_iCheckBoxSelectedCount = 0; 
		}
		
		for (int row = 0; row < rowCount; row++){
			QFileNameItem *item = static_cast<QFileNameItem *>(cellWidget(row, 0));
			item->m_checkBox->setCheckState(state);
			//选中后改变背景颜色
			if ((Qt::CheckState)state == Qt::Checked){
				setRowColor(row, m_selectedBkColor);
			}else{
				setRowColor(row, m_defaultBkColor);
			}
		}
	});

	connect(this, &QBaseTableWidget::cellEntered, this, &QBaseTableWidget::slotCellEntered);
	connect(this, &QBaseTableWidget::cellClicked, this, &QBaseTableWidget::slotCellClicked);
	connect(this, &QBaseTableWidget::cellDoubleClicked, this, &QBaseTableWidget::slotCellDoubleClicked);

	//创建右键弹出菜单
	createAction();
}

QBaseTableWidget::~QBaseTableWidget()
{
	delete m_chkBox;
	delete m_popMenu;
	delete m_openAction;
	delete m_renameAction;
	delete m_downloadAction;
	delete m_uploadAction;
	delete m_createFolderAction;
	delete m_flushAction;

	clearAllRows();
}

void QBaseTableWidget::createAction()
{
	m_popMenu = new QMenu;
	m_openAction = new QAction(this);
	m_renameAction = new QAction(this);
	m_downloadAction = new QAction(this);
	m_uploadAction = new QAction(this);
	m_createFolderAction = new QAction(this);
	m_flushAction = new QAction(this);
	m_deleteAction = new QAction(this);

	m_openAction->setText(QStringLiteral("打开"));
	m_renameAction->setText(QStringLiteral("重命名"));
	m_downloadAction->setText(QStringLiteral("下载"));
	m_uploadAction->setText(QStringLiteral("上传"));
	m_createFolderAction->setText(QStringLiteral("新建文件夹"));
	m_flushAction->setText(QStringLiteral("刷新"));
	m_deleteAction->setText(QStringLiteral("删除"));

	m_flushAction->setShortcut(QKeySequence::Refresh);
}

void QBaseTableWidget::contextMenuEvent(QContextMenuEvent *event)
{
	m_popMenu->clear();
	QPoint point = event->pos();

	m_popMenu->addAction(m_renameAction);
	m_popMenu->addAction(m_flushAction);

	QTableWidgetItem *item = this->itemAt(point);
	if (item != NULL){
		
		connect(m_renameAction, &QAction::triggered, [=](){
			
		});
	}else{

	}

	m_popMenu->exec(QCursor::pos());
	event->accept();
}

void QBaseTableWidget::mouseMoveEvent(QMouseEvent *event)
{
	QPoint point = event->pos();
	QTableWidgetItem *pItem = itemAt(point);
	if (pItem == nullptr){
		QFileNameItem *itemWidget = static_cast<QFileNameItem *>(cellWidget(m_previousStatus.previousRow, 0));
		if (itemWidget){
			itemWidget->setToolButtonVisible(false);
			setRowColor(m_previousStatus.previousRow, m_previousStatus.previousColor);
		}
	}
	QTableWidget::mouseMoveEvent(event);
}

void QBaseTableWidget::setFileInfo(QList<FILE_INFO> fileInfo)
{
	m_fileInfo = fileInfo;
}

void QBaseTableWidget::setHorizontalHeader(QStringList header)
{
	setColumnCount(header.count());
	setColumnWidth(0, 350);
	setHorizontalHeaderLabels(header);
}

void QBaseTableWidget::insertTableItem()
{
	for (auto it = m_fileInfo.begin(); it != m_fileInfo.end(); it++){
		int row = rowCount();
		setRowCount(row + 1);
		FILE_INFO fileInfo = static_cast<FILE_INFO>(*it);
		QTableWidgetItem *item = new QTableWidgetItem("");
		setItem(row, 0, item);
		//QFileNameItem *fileNameItem = new QFileNameItem(fileInfo.fileName,fileInfo.bDir,this);
		//fileNameItem->setToolButtonVisible(false);
		//fileNameItem->setStyleSheet("background:blue;");
		//setCellWidget(row, 0, fileNameItem);
		//setItem(row, 1, new QTableWidgetItem(fileInfo.fileName));
		//setColumnHidden(1,true);
		setItem(row, 1, new QTableWidgetItem(QString::number(row)/*fileInfo.fileInfo1*/));
		setItem(row, 2, new QTableWidgetItem(fileInfo.fileInfo2));
		setItem(row, 3, new QTableWidgetItem(fileInfo.fileInfo3));
	}
}

void QBaseTableWidget::setCheckBoxStatus(int state)
{
	m_chkBox->setCheckState((Qt::CheckState)state);
}

void QBaseTableWidget::setRowColor(int row, QColor color)
{
	//QFileNameItem *item = static_cast<QFileNameItem *>(cellWidget(row, 0));
	//item->setBackgroundColor(color);
	for (int col = 0; col < columnCount(); col++){
		QTableWidgetItem *item = this->item(row, col);
		item->setBackgroundColor(color);
	}
}

int QBaseTableWidget::getRowCount()
{
	return rowCount();
}

void QBaseTableWidget::checkBoxSelectedCountIncrease()
{
	m_iCheckBoxSelectedCount++;
	if (m_iCheckBoxSelectedCount == rowCount()){
		m_chkBox->setCheckState(Qt::Checked);
	}
}

void QBaseTableWidget::checkBoxSelectedCountDecrease()
{
	m_iCheckBoxSelectedCount--;
	m_chkBox->setCheckState(Qt::Unchecked);
}

int QBaseTableWidget::getCheckBoxSelectedCount()
{
	int iCount = 0;
	int rowCount = this->rowCount();
	for (int row = 0; row < rowCount; row++){
		QFileNameItem *item = static_cast<QFileNameItem *>(cellWidget(row, 0));
		if (item->m_checkBox->checkState() == Qt::Checked){
			iCount++;
		}
	}
	return iCount;
}

void QBaseTableWidget::clearAllRows()
{
	int rowCount = getRowCount();
	for (int i = 0; i < rowCount; i++){
		QFileNameItem *item = static_cast<QFileNameItem *>(cellWidget(i, 0));
		delete item;
	}
	setRowCount(0);
	clearContents();
}

/*============slots==============*/
void QBaseTableWidget::slotCellEntered(int row, int column)
{
	Q_UNUSED(column);

	QFileNameItem *itemWidget = static_cast<QFileNameItem *>(cellWidget(m_previousStatus.previousRow, 0));
	if (itemWidget){
		itemWidget->setToolButtonVisible(false);
	}
	itemWidget = static_cast<QFileNameItem *>(cellWidget(row, 0));
	itemWidget->setToolButtonVisible(true);

	QTableWidgetItem *item = nullptr;
	item = this->item(m_previousStatus.previousRow, 1);
	if (item != 0){
		setRowColor(m_previousStatus.previousRow, m_previousStatus.previousColor);
	}

	item = this->item(row, 1);
	if (item != 0){
		setRowColor(row, m_hoverBkColor);
		if (item->isSelected() || m_chkBox->isChecked()){
			m_previousStatus.previousColor = m_selectedBkColor;
		}else{
			m_previousStatus.previousColor = m_defaultBkColor;
		}
	}
	m_previousStatus.previousRow = row;
}

void QBaseTableWidget::slotCellClicked(int row, int column)
{
	Q_UNUSED(column);
	//setRowColor(row, m_selectedBkColor);
}

void QBaseTableWidget::slotCellDoubleClicked(int row, int column)
{

}

void QBaseTableWidget::slotSortByColumn(int column){
	//sortByColumn(column);
	switch (column)
	{
		case 0:
		case 2:
		//sortByColumn(column+1);
		break;
	default:
		sortByColumn(column);
		break;
	}
}

void QBaseTableWidget::slotSectionEntered(int logicalIndex)
{
	Q_UNUSED(logicalIndex);
	QFileNameItem *itemWidget = static_cast<QFileNameItem *>(cellWidget(m_previousStatus.previousRow, 0));
	if (itemWidget){
		itemWidget->setToolButtonVisible(false);
		setRowColor(m_previousStatus.previousRow, m_previousStatus.previousColor);
	}
}