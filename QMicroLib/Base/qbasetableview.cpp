#include "qbasetableview.h"
#include "Dialogs/qfilenameitem.h"
#include <QRegExp>
#include <QDebug>
#include "Delegate/qwidgetdelegate.h"

QBaseTableView::QBaseTableView(QWidget *parent)
	: QTableView(parent),
	m_pHeaderView(nullptr),
	m_curRow(-1),
	m_iCheckBoxSelectedCount(0),
	m_childNodes(NULL)
{
	setFrameShape(QFrame::NoFrame);//�����ޱ߿�
	setShowGrid(false);//���ò���ʾ������
	setItemDelegate(new QNoFocusDelegate);   //ȥ������������
	setSelectionMode(QAbstractItemView::ExtendedSelection);//�ɶ�ѡ��Ctrl��Shrift��Ctrl+A�����ԣ�
	//setSelectionMode(QAbstractItemView::MultiSelection);
	setSelectionBehavior(QAbstractItemView::SelectRows); //����ѡ����Ϊʱÿ��ѡ��һ��
	//setSelectionMode(QAbstractItemView::SingleSelection);
	setEditTriggers(QAbstractItemView::NoEditTriggers);

	QHeaderView *verticalHeaderView = verticalHeader();
	verticalHeaderView->setDefaultSectionSize(25);
	verticalHeaderView->setVisible(false);//���ô�ֱͷ���ɼ�
	setMouseTracking(true);
	setSortingEnabled(true);
	//sortByColumn(FILE_NAME_COLUMN, Qt::AscendingOrder);

	//�����Զ���ı�ͷ
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
	connect(m_pHeaderView, &QBaseHeaderView::stateChanged, this, &QBaseTableView::slotCheckBoxStateChanged);

	//����model��ʾ����
	m_pModel = new QTableModel(this);
	m_pSortMode = new QSortFilterModel;
	setModel(m_pSortMode);
	m_pSortMode->setSourceModel(m_pModel);
	//m_pSortMode->sort(FILE_SIZE_COLUMN, Qt::AscendingOrder);

	//setItemDelegateForColumn(FILE_NAME_COLUMN, new QWidgetDelegate);

	connect(this, &QBaseTableView::clicked, [=](const QModelIndex &index){
		int row = index.row();
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
	deleteWidget();
}

QFileNameItem *QBaseTableView::getWidget(int row)
{
	QModelIndex index = model()->index(row, CHECK_BOX_COLUMN);
	return static_cast<QFileNameItem *>(indexWidget(index));
}

QTableModel *QBaseTableView::getTableModel()
{
	return m_pModel;
}

void QBaseTableView::initHeaderView(QStringList header)
{
	m_pModel->setHorizontalHeaderList(header);
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
	setColumnWidth(0, 350);     //���õ�1�еĿ��
	//setColumnWidth(1, 350);     //���õ�1�еĿ��
	setColumnHidden(FILE_NAME_COLUMN, true);
	setColumnHidden(FILE_AUTHOR_CLOUMN, true);

	updateFirstColumn();
	//�������ݺ�����Ĭ������ʽ
	//m_pSortMode->sort(FILE_NAME_COLUMN, Qt::AscendingOrder);
}

void QBaseTableView::addIndexWidget(QModelIndex index, CFileNode *pNode)
{
	QFileNameItem *widget = new QFileNameItem(pNode, this);
	connect(widget, &QFileNameItem::sigSetChecked, [=](){
		setCheckBoxState();
	});
	connect(widget, &QFileNameItem::sigChangeDir, this, &QBaseTableView::slotChangeDir);
	m_pList.push_back(widget);
	widget->setToolButtonVisible(false);
	setIndexWidget(index, widget);
}

void QBaseTableView::updateRow(int row)
{
	if (row == m_curRow)
		return;

	QFileNameItem *widget = NULL;
	if (m_curRow >= 0){
		widget = getWidget(m_curRow);
		if (widget){
			widget->setToolButtonVisible(false);
		}
	}
	if (row >= 0){
		widget = getWidget(m_curRow);
		if (widget){
			getWidget(row)->setToolButtonVisible(true);
		}
	}
	
	m_pModel->setHoverRow(row);
	int column_count = model()->columnCount();
	for (int i = column_count - 1; i >= 0; i--){
		update(model()->index(m_curRow, i));
		update(model()->index(row, i));
	}
	m_curRow = row;
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
		setAllRowsSelect();
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

	CFileNode *fileNode = new CFileNode(QStringLiteral("�½��ļ���"), "10240", "2017-06-07 12:22", "eeee", "22ddd222", true);
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
		int row = model_index.row();
		if (!list_row.contains(row))
			list_row.append(row);
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

void QBaseTableView::setAllRowsSelect()
{
	int nRows = model()->rowCount();
	QItemSelectionModel* selection_model = selectionModel();
	QItemSelection selection;

	QModelIndex left = model()->index(0, 0);
	QModelIndex right = model()->index(nRows - 1, model()->columnCount() - 1);
	QItemSelection sel(left, right);
	selection.merge(sel, QItemSelectionModel::Select);  //��ÿһ����Ԫ��/ÿһ�ж���Ϊһ��QItemSelection ���󣬲�ƴ�ӵ��ܵ�QItemSelection ������  
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

//�����ļ����Ͳ������е��ļ�
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