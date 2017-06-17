#include "qmicrolib.h"
#include "Common/qxmlparser.h"

QMicroLib::QMicroLib(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowMinMaxButtonsHint;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);
	setFixedWidth(900);
	setFixedHeight(550);

	m_pLayout = new QHBoxLayout(this);

	m_navWidget = new QNavigateWidget;
	m_pLayout->addWidget(m_navWidget);

	m_rightVBoxLayout = new QVBoxLayout(this);

	m_toolBarWidget = new QToolBarWidget();
	m_rightVBoxLayout->addWidget(m_toolBarWidget);

	m_tableView = new QBaseTableView(this);
	QStringList header;
	header << "" << QStringLiteral("文件名") << QStringLiteral("提交者") << QStringLiteral("大小") << QStringLiteral("时间") << QStringLiteral("路径");
	m_tableView->initHeaderView(header);

	QXMLParser xml;
	xml.openXML("data.xml");

	CFileNode *fileNode = xml.getFileNode();

	//CFileNode *fileNode = new CFileNode(QStringLiteral("文件"), "123", "2017-06-07", "1111", "22222", true);
	//CFileNode *fileNode1 = new CFileNode(QStringLiteral("我的文件夹"), "1024" , "2017-06-07 14:51", "1111", "22222", true);
	//fileNode->append(fileNode1);
	//CFileNode *fileNode2 = new CFileNode(QStringLiteral("我的文档.docx"), "2048", "2017-06-07 14:52", "1111", "22222", false);
	//fileNode->append(fileNode2);
	//CFileNode *fileNode3 = new CFileNode(QStringLiteral("表格.xls"), "4096", "2017-06-07 14:53", "1111", "22222", false);
	//fileNode->append(fileNode3);
	//CFileNode *fileNode4 = new CFileNode(QStringLiteral("计划.ppt"), "8192", "2017-06-07 14:54", "1111", "22222", false);
	//fileNode->append(fileNode4);
	//CFileNode *fileNode5 = new CFileNode(QStringLiteral("图片.png"), "81920", "2017-06-07 14:57", "1111", "22222", false);
	//fileNode->append(fileNode5);
	//fileNode1->append(fileNode2);
	//fileNode1->append(fileNode3);
	//fileNode1->append(fileNode4);
	//fileNode1->append(fileNode5);
	m_tableView->setModelData(&fileNode->m_childNodes);
	m_tableView->showTable(&fileNode->m_childNodes);

	m_titleBarWidget = new QTableTitleBarWidget(fileNode);
	m_rightVBoxLayout->addWidget(m_titleBarWidget);

	connect(m_toolBarWidget, &QToolBarWidget::deleteClicked, m_tableView, &QBaseTableView::slotDeleteRow);
	connect(m_toolBarWidget, &QToolBarWidget::newFileClicked,m_tableView,&QBaseTableView::slotAddRow);
	connect(m_toolBarWidget, &QToolBarWidget::searchClicked, m_tableView, &QBaseTableView::slotFilter);
	connect(m_toolBarWidget, &QToolBarWidget::sigTextChanged, m_tableView, &QBaseTableView::slotEmptyFilter);

	connect(m_navWidget, &QNavigateWidget::sigAllFiles, m_tableView, &QBaseTableView::slotShowAllFiles);
	connect(m_navWidget, &QNavigateWidget::sigWord, m_tableView, &QBaseTableView::slotShowWordFiles);
	connect(m_navWidget, &QNavigateWidget::sigExcel, m_tableView, &QBaseTableView::slotShowExcelFiles);
	connect(m_navWidget, &QNavigateWidget::sigPPT, m_tableView, &QBaseTableView::slotShowPPTFiles);
	connect(m_navWidget, &QNavigateWidget::sigImage, m_tableView, &QBaseTableView::slotShowImageFiles);
	connect(m_navWidget, &QNavigateWidget::sigMovie, m_tableView, &QBaseTableView::slotShowMovieFiles);
	connect(m_navWidget, &QNavigateWidget::sigOther, m_tableView, &QBaseTableView::slotShowOtherFiles);

	connect(m_tableView, &QBaseTableView::sigChangeDir, m_titleBarWidget, &QTableTitleBarWidget::slotAddWidget);
	connect(m_titleBarWidget, &QTableTitleBarWidget::sigBack, m_tableView, &QBaseTableView::slotBackDir);

	m_rightVBoxLayout->addWidget(m_tableView);
	m_rightVBoxLayout->setContentsMargins(0, 0, 0, 0);
	m_rightVBoxLayout->setSpacing(2);

	m_pLayout->addLayout(m_rightVBoxLayout);
	m_pLayout->setContentsMargins(0, 0, 0, 0);
	m_pLayout->setSpacing(0);
}

QMicroLib::~QMicroLib()
{
	delete m_navWidget;
	delete m_toolBarWidget;
	delete m_titleBarWidget;
	delete m_tableView;
	delete m_rightVBoxLayout;
	delete m_pLayout;
}
