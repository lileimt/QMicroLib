#include "qbasetableview.h"
#include <QRegExp>
#include "Dialogs/qfilenameitem.h"
#include "Delegate/qwidgetdelegate.h"
#include "Delegate/qnofocusDelegate.h"
#include <QDebug>

QBaseTableView::QBaseTableView(QWidget *parent)
	: QTableView(parent),
	m_pHeaderView(nullptr),
	m_curRow(-1),
	m_curRightRow(-1),
	m_iCheckBoxSelectedCount(0),
	m_childNodes(NULL)
{
	setFrameShape(QFrame::NoFrame);//设置无边框
	setShowGrid(false);//设置不显示格子线
	setItemDelegate(new QNoFocusDelegate);   //去掉鼠标点击的虚框
	setSelectionMode(QAbstractItemView::ExtendedSelection);//可多选（Ctrl、Shrift、Ctrl+A都可以）
	//setSelectionMode(QAbstractItemView::MultiSelection);
	setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为时每次选择一行
	//setSelectionMode(QAbstractItemView::SingleSelection);
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, &QBaseTableView::customContextMenuRequested, this, &QBaseTableView::slotContextMenu);
	createAction();            //文件的右键菜单
	createEmptyAction();  //空白区域的右键菜单

	QHeaderView *verticalHeaderView = verticalHeader();
	verticalHeaderView->setDefaultSectionSize(25);
	verticalHeaderView->setVisible(false);//设置垂直头不可见
	setMouseTracking(true);
	setSortingEnabled(true);
	//sortByColumn(FILE_NAME_COLUMN, Qt::AscendingOrder);

	//设置自定义的表头
	m_pHeaderView = new QBaseHeaderView(Qt::Horizontal,this);
	setHorizontalHeader(m_pHeaderView);
	m_pHeaderView->setSortIndicator(0, Qt::AscendingOrder);
	m_pHeaderView->setSortIndicator(1, Qt::AscendingOrder);
	m_pHeaderView->setSortIndicator(2, Qt::AscendingOrder);
	m_pHeaderView->setSortIndicatorShown(true);
	m_pHeaderView->setSectionsClickable(true);
	connect(m_pHeaderView, &QBaseHeaderView::headerEntered, [=](){
		QFileNameItem *widget = getWidget(0);
		if (widget){
			widget->setToolButtonVisible(false);
		}
		resetRow();
	});
	connect(m_pHeaderView, &QBaseHeaderView::sectionClicked, [=](){
		resetRow();
	});
	connect(m_pHeaderView, &QBaseHeaderView::stateChanged, this, &QBaseTableView::slotCheckBoxStateChanged);

	//设置model显示数据
	m_pModel = new QTableModel(this);
	m_pSortMode = new QSortFilterModel;
	setModel(m_pSortMode);
	m_pSortMode->setSourceModel(m_pModel);
	//m_pSortMode->sort(FILE_SIZE_COLUMN, Qt::AscendingOrder);

	//setItemDelegateForColumn(FILE_NAME_COLUMN, new QWidgetDelegate);

	connect(this, &QBaseTableView::clicked, [=](const QModelIndex &index){
		int row = index.row();
		//QModelIndex _index = model()->index(index.row(), FILE_NAME_COLUMN);
		setCurrentIndex(index);
		//clearSelection();
		int nRows = model()->rowCount();
		for (int i = 0; i < nRows; i++){
			if (i == row){
				getWidget(i)->m_checkBox->setChecked(true);
			}else{
				getWidget(i)->m_checkBox->setChecked(false);
			}
		}
		if (nRows != 1){
			m_pHeaderView->setCheckBoxState(false);
		}else{
			m_pHeaderView->setCheckBoxState(true);
		}
	});
}

QBaseTableView::~QBaseTableView()
{
	delete m_pHeaderView;
	delete m_pModel;
	delete m_pSortMode;
	delete m_popMenu;
	delete m_popEmptyMenu;
	delete m_openAction;
	delete m_downloadAction;
	delete m_shareAction;
	delete m_renameAction;
	delete m_deleteAction;
	delete m_attributeAction;
	delete m_newDirAction;
	delete m_uploadAction;
	deleteWidget();
}

QFileNameItem *QBaseTableView::getWidget(int row)
{
	QModelIndex index = model()->index(row, CHECK_BOX_COLUMN);
	return static_cast<QFileNameItem *>(indexWidget(index));
}

int QBaseTableView::getHeaderWidth(int index)
{
	return m_pHeaderView->sectionSize(index);
}

QTableModel *QBaseTableView::getTableModel()
{
	return m_pModel;
}

void QBaseTableView::initHeaderView(QStringList header)
{
	m_pModel->setHorizontalHeaderList(header);
	sortByColumn(CHECK_BOX_COLUMN, Qt::AscendingOrder);
}

void QBaseTableView::setModelData(QList<CFileNode *> *childNodes)
{
	m_childNodes = childNodes;
}

void QBaseTableView::showTable(QList<CFileNode *> *childNodes)
{
	m_pHeaderView->setCheckBoxState(false);
	m_pModel->setModelData(childNodes);
	m_pModel->refreshModel();
	setColumnWidth(0, 350);     //设置第1列的宽度
	//setColumnWidth(1, 350);     //设置第1列的宽度
	//setColumnHidden(FILE_NAME_COLUMN, true);
	setColumnHidden(FILE_AUTHOR_CLOUMN, true);

	updateFirstColumn();
	//插入数据后设置默认排序方式
	//m_pSortMode->sort(FILE_NAME_COLUMN, Qt::AscendingOrder);
}

void QBaseTableView::addIndexWidget(QModelIndex index, CFileNode *pNode)
{
	QFileNameItem *widget = new QFileNameItem(pNode, this);
	connect(widget, &QFileNameItem::sigSetChecked, [=](){
		setCheckBoxState();
	});
	connect(widget, &QFileNameItem::sigChangeDir, this, &QBaseTableView::slotChangeDir);
	//connect(widget, &QFileNameItem::clicked, [=](){
		//setCurrentIndex(model()->index(index.row(),1));
	//});
	m_pList.push_back(widget);
	widget->setToolButtonVisible(false);
	setIndexWidget(index, widget);
}

void QBaseTableView::updateRow(int row)
{
	if (row == m_curRow)
		return;

	if (row >= 0){
		QFileNameItem *widget = getWidget(row);
		if (widget){
			widget->setToolButtonVisible(true);
		}
	}
	if (m_curRow >= 0){
		QFileNameItem *widget = getWidget(m_curRow);
		if (widget){
			widget->setToolButtonVisible(false);
		}
	}
	
	m_pModel->setHoverRow(row);
	int column_count = model()->columnCount();
	for (int i = column_count - 1; i >= 0; i--){
		update(model()->index(m_curRow, i));
		update(model()->index(row, i));
	}
	m_curRow = row;

	QFileNameItem *widget = getWidget(m_curRow);
	if (widget){
		getWidget(row)->setToolButtonVisible(true);
	}
}

void QBaseTableView::mouseMoveEvent(QMouseEvent *event)
{
	int row = indexAt(event->pos()).row();
	updateRow(row);
}

void QBaseTableView::leaveEvent(QEvent *event)
{
	Q_UNUSED(event);
	resetRow();
}

void QBaseTableView::resetRow()
{
	m_pModel->setHoverRow(-1);
	int columnCount = model()->columnCount();
	for (int i = columnCount - 1; i >= 0; i--){
		update(model()->index(m_curRow, i));
	}
	m_curRow = -1;
}

void QBaseTableView::slotCheckBoxStateChanged(bool bChecked)
{
	int rowCount = m_pModel->rowCount();
	if (bChecked){
		m_iCheckBoxSelectedCount = rowCount;
		selectAll();
	}else{
		m_iCheckBoxSelectedCount = 0;
		clearSelection();
	}
	for (int i = 0; i < rowCount; i++){
		QFileNameItem *widget = getWidget(i);
		if (bChecked){
			widget->m_checkBox->setCheckState(Qt::Checked);
		}
		else{
			widget->m_checkBox->setCheckState(Qt::Unchecked);
		}
	}
}

void QBaseTableView::setCheckBoxState()
{
	int count = 0;
	int nRows = model()->rowCount();
	for (int i = 0; i < nRows; i++){
		QFileNameItem *widget = getWidget(i);
		if (widget->m_checkBox->checkState() == Qt::Checked){
			count++;
		}else{
			break;
		}
	}
	if (count == nRows){
		m_pHeaderView->setCheckBoxState(true);
	}else{
		m_pHeaderView->setCheckBoxState(false);
	}
}

void QBaseTableView::slotAddRow()
{
	m_pHeaderView->setCheckBoxState(false);
	slotCheckBoxStateChanged(false);

	CFileNode *fileNode = new CFileNode(QStringLiteral("新建文件夹"), "", "2017-06-07 12:22", "", "", true);
	m_childNodes->insert(0, fileNode);
	m_pModel->refreshModel();

	updateFirstColumn();

	getWidget(0)->m_checkBox->setCheckState(Qt::Checked);
}

void QBaseTableView::slotDeleteRow()
{
	QModelIndexList model_index_list = this->selectedIndexes();
	int model_count = model_index_list.count();
	if (model_count <= 0)
		return;

	QList<int> list_row;
	for (int i = model_count - 1; i >= 0; i--)
	{
		QModelIndex model_index = model_index_list.at(i);
		int realRow = -1;
		getRealIndex(m_childNodes, model_index.row(), realRow);
		if (!list_row.contains(realRow))
			list_row.append(realRow);
	}

	if (list_row.isEmpty())
		return;

	qSort(list_row);

	for (int i = list_row.count() - 1; i >= 0; i--)
	{
		m_childNodes->removeAt(list_row.at(i));
	}
	m_pModel->refreshModel();
	updateFirstColumn();
}

void QBaseTableView::updateFirstColumn()
{
	deleteWidget();
	
	int nRows = model()->rowCount();
	for (int i = 0; i < nRows; i++){
		QModelIndex index = model()->index(i, CHECK_BOX_COLUMN);
		QVariant v = model()->data(index, Qt::UserRole);
		CFileNode *node = (CFileNode *)v.value<void *>();
		addIndexWidget(index, node);
	}
}

void QBaseTableView::setRowSelect(int startRow,int endRow)
{
	QItemSelectionModel* selection_model = selectionModel();
	QItemSelection selection;

	QModelIndex left = model()->index(startRow, 0);
	QModelIndex right = model()->index(endRow - 1, model()->columnCount() - 1);
	QItemSelection sel(left, right);
	selection.merge(sel, QItemSelectionModel::Select);  //将每一个单元格/每一行都作为一个QItemSelection 对象，并拼接到总的QItemSelection 对象中  
	selection_model->select(selection, QItemSelectionModel::Select);
}

void QBaseTableView::deleteWidget()
{
	if (m_pList.size() == 0)return;
	QList<QFileNameItem *>::iterator it = m_pList.begin();
	for (; it != m_pList.end();){
		QFileNameItem *item = static_cast<QFileNameItem *>(*it);
		if (item){
			delete item;
			item = NULL;
		}
		it = m_pList.erase(it);
	}
	//qDebug() << m_pList.size();
}

void QBaseTableView::slotFilter(QString text)
{
	//QRegExp regExp(text, Qt::CaseInsensitive);
	//m_pSortMode->setFilterRegExp(regExp);
	//m_pSortMode->setFilterKeyColumn(FILE_NAME_COLUMN);
	//m_pSortMode->setCondition(text);
	m_filterNodes.clear();
	//filterFileNodes(text);
	getAllFilesByType(m_childNodes, text);
	showTable(&m_filterNodes);
}

void QBaseTableView::filterFileNodes(QString strText)
{
	if (strText.isEmpty())return;
	QRegExp regExp(strText);
	QList<CFileNode *>::iterator it = m_childNodes->begin();
	for (; it != m_childNodes->end(); it++){
		CFileNode *node = static_cast<CFileNode *>(*it);
		if (node->m_fileName.indexOf(regExp) != -1){
			m_filterNodes.push_back(node);
		}
	}
}

//根据文件类型查找所有的文件
void QBaseTableView::getAllFilesByType(QList<CFileNode *> *childNodes, QString strText)
{
	if (childNodes == NULL)return;
	QRegExp regExp(strText);
	QList<CFileNode *>::iterator it = childNodes->begin();
	for (; it != childNodes->end(); it++){
		CFileNode *node = static_cast<CFileNode *>(*it);
		if (node->m_fileName.indexOf(regExp) != -1){
			m_filterNodes.push_back(node);
		}
		getAllFilesByType(&node->m_childNodes, strText);
	}
}

void QBaseTableView::slotEmptyFilter(const QString &text)
{
	Q_UNUSED(text);
	showTable(m_childNodes);
}

void QBaseTableView::slotShowAllFiles()
{
	showTable(m_childNodes);
}

void QBaseTableView::slotShowWordFiles()
{
	slotFilter(".doc");
}

void QBaseTableView::slotShowExcelFiles()
{
	slotFilter(".xls");
}

void QBaseTableView::slotShowPPTFiles()
{
	slotFilter(".ppt");
}

void QBaseTableView::slotShowImageFiles()
{
	slotFilter(".png|.ico|.jpg|.jpeg|.bmp|.gif");
}

void QBaseTableView::slotShowMovieFiles()
{
	slotFilter(".avi|.mp4|.rmvb|.mkv|.wmv|.mp3");
}

void QBaseTableView::slotShowOtherFiles()
{

}

void	QBaseTableView::slotChangeDir(CFileNode *pNode)
{
	showTable(&pNode->m_childNodes);
	emit sigChangeDir(pNode);
}

void QBaseTableView::slotBackDir(CFileNode *pNode)
{
	showTable(&pNode->m_childNodes);
}

void QBaseTableView::slotContextMenu(QPoint point)
{
	QModelIndex index = this->indexAt(point);
	qDebug() << point << index.row();
	if (index.isValid()){
		m_curRightRow = index.row();
		m_popMenu->exec(QCursor::pos());
	}else{
		m_popEmptyMenu->exec(QCursor::pos());
	}
}

void QBaseTableView::createAction()
{
	m_popMenu = new QMenu(this);
	m_openAction = new QAction(QStringLiteral("打开"),this);
	m_downloadAction = new QAction(QStringLiteral("下载"), this);
	m_shareAction = new QAction(QIcon(":/toolbar/share"),QStringLiteral("分享"), this);
	m_renameAction = new QAction(QStringLiteral("重命名"), this);
	m_deleteAction = new QAction(QStringLiteral("删除"), this);
	m_attributeAction = new QAction(QStringLiteral("属性"), this);

	m_popMenu->addAction(m_openAction);
	m_popMenu->addSeparator();
	m_popMenu->addAction(m_downloadAction);
	m_popMenu->addAction(m_shareAction);
	m_popMenu->addAction(m_renameAction);
	m_popMenu->addAction(m_deleteAction);
	m_popMenu->addSeparator();
	m_popMenu->addAction(m_attributeAction);

	connect(m_openAction, &QAction::triggered, [=](){
		int realRow = -1;
		CFileNode *pNode = getRealIndex(m_childNodes, m_curRightRow, realRow);
		if (pNode->m_bDir){
			showTable(&pNode->m_childNodes);
			emit sigChangeDir(pNode);
		}
	});
	connect(m_downloadAction, &QAction::triggered, [=](){
		qDebug() << "download";
	});
	connect(m_shareAction, &QAction::triggered, [=](){
		qDebug() << "share";
	});
	connect(m_renameAction, &QAction::triggered, [=](){
		getWidget(m_curRightRow)->showFileNameEdit();
	});
	connect(m_deleteAction, &QAction::triggered, [=](){
		int realRow = 0;
		getRealIndex(m_childNodes, m_curRightRow, realRow);
		m_childNodes->removeAt(realRow);
		m_pModel->refreshModel();
		updateFirstColumn();
	});

	connect(m_attributeAction, &QAction::triggered, [=](){
		qDebug() << "attribute";
	});
}

void QBaseTableView::createEmptyAction()
{
	m_popEmptyMenu = new QMenu(this);
	m_newDirAction = new QAction(QStringLiteral("新建文件夹"), this);
	m_uploadAction = new QAction(QStringLiteral("上传"), this);

	m_popEmptyMenu->addAction(m_newDirAction);
	m_popEmptyMenu->addAction(m_uploadAction);

	connect(m_newDirAction, &QAction::triggered, [=](){
		slotAddRow();
	});
	connect(m_uploadAction, &QAction::triggered, [=](){
		
	});
}

void QBaseTableView::renameAction(int row)
{
	QFileNameItem *item = (	QFileNameItem *)getWidget(row);
	item->showFileNameEdit();
	qDebug() << row<<item->m_lineEdit;
}

CFileNode *QBaseTableView::getRealIndex(QList<CFileNode *> *childNodes, int curRow, int &realRow)
{
	int count = 0;
	QVariant variant = model()->data(model()->index(curRow, CHECK_BOX_COLUMN), Qt::UserRole);
	CFileNode *pNode = (CFileNode *)variant.value<void *>();
	//qDebug() << pNode->m_fileName;
	QList<CFileNode *>::iterator it = childNodes->begin();
	for (; it != childNodes->end(); it++){
		CFileNode *pListNode = static_cast<CFileNode *>(*it);
		if (!pListNode->m_fileName.compare(pNode->m_fileName)){
			realRow = count;
			return pListNode;
		}
		count++;
	}
	return NULL;
}