#include "qtabletitlebarwidget.h"
#include <QDebug>

QTableTitleBarWidget::QTableTitleBarWidget(CFileNode *pNode,QWidget *parent)
	: QBaseWidget(parent),
	m_sumWidth(0),
	m_bListView(true),
	m_pNode(pNode)
{
	ui.setupUi(this);
	ui.wdtNavigate->setStyleSheet("border:1px solid black;");

	m_pLayout = new QHBoxLayout(ui.wdtNavigate);
	m_pLayout->setContentsMargins(2, 0, 0, 0);
	m_pLayout->setAlignment(Qt::AlignLeft);
	m_pLayout->setSpacing(4);

	ui.btnView->installEventFilter(this);
	connect(ui.btnView, &QToolButton::clicked, [=](){
		//qDebug() << m_bListView;
		m_bListView = !m_bListView;
		if (m_bListView){
			ui.btnView->setStyleSheet("border-image:url(:/toolbar/detailview_hover);");
		}else{
			ui.btnView->setStyleSheet("border-image:url(:/toolbar/view_hover);");
		}
	});
	connect(ui.btnBack, &QToolButton::clicked, this, &QTableTitleBarWidget::slotBack);

	CFileNode fileNode(QStringLiteral("我的网盘"), "", "", "", "", true);
	addWidget(&fileNode,true);

	/*CFileNode fileNode1(QStringLiteral("我的网盘1"), "", "", "", "", true);
	addWidget(&fileNode1);
	CFileNode fileNode2(QStringLiteral("我的网盘2"), "", "", "", "", true);
	addWidget(&fileNode2);*/
}

QTableTitleBarWidget::~QTableTitleBarWidget()
{
	delete m_pLayout;
	clearPathItem();
}

void QTableTitleBarWidget::addWidget(CFileNode *fileNode,bool bHome)
{
	m_pNode = fileNode;
	QPathItem *pathItem = new QPathItem(fileNode, bHome);
	m_pLayout->addWidget(pathItem);
	pathItem->setIndex(m_pathItems.size());
	m_pathItems.push_back(pathItem);
	connect(pathItem, &QPathItem::sigClicked, this, &QTableTitleBarWidget::slotRemovePathItem);
	m_sumWidth += pathItem->getWidth();
	if (m_sumWidth >= width()){   //计算显示的宽度，重新放置窗口

	}
}

void QTableTitleBarWidget::delWidget(int nIndex)
{
	QPathItem *pathItem = m_pathItems.at(nIndex);
	m_pLayout->removeWidget(pathItem);
	bool bDelete = false;
	auto it = m_pathItems.begin();
	for (; it != m_pathItems.end(); ){
		if (*it == pathItem){     //获取到当前窗口的迭代器
			bDelete = true;
			//it++;
			//continue;
		}
		if (bDelete){  //删除被选中之后的元素
			delete *it;
			it = m_pathItems.erase(it);
		}else{
			it++;
		}
	}
}

bool QTableTitleBarWidget::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == ui.btnView){
		if (event->type() == QEvent::Enter){
			if (m_bListView){
				ui.btnView->setStyleSheet("border-image:url(:/toolbar/detailview_hover);");
			}else{
				ui.btnView->setStyleSheet("border-image:url(:/toolbar/view_hover);");
			}
		}else if (event->type() == QEvent::Leave){
			if (m_bListView){
				ui.btnView->setStyleSheet("border-image:url(:/toolbar/detailview);");
			}else{
				ui.btnView->setStyleSheet("border-image:url(:/toolbar/view);");
			}
		}
	}
	return QWidget::eventFilter(watched, event);
}

void QTableTitleBarWidget::slotRemovePathItem(int nIndex)
{
	if (nIndex == m_pathItems.size()-1)return;
	removeItem(nIndex + 1);
}

void QTableTitleBarWidget::slotBack()
{
	if (m_pathItems.size() == 1)return;
	removeItem(m_pathItems.size() - 1);
}

void QTableTitleBarWidget::clearPathItem()
{
	QVector<QPathItem *>::iterator it = m_pathItems.begin();
	for (; it != m_pathItems.end();it++){
		delete (*it);
	}
	m_pathItems.clear();
}

void QTableTitleBarWidget::slotAddWidget(CFileNode *pNode)
{
	addWidget(pNode);
}

void QTableTitleBarWidget::removeItem(int nIndex)
{
	QPathItem *pathItem = m_pathItems.at(nIndex);
	emit sigBack(pathItem->getCurNode()->m_parent);
	delWidget(nIndex);
}