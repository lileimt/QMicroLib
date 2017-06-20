#include "qfilenameitem.h"
//#include "common/iconhelper.h"
#include "common/commonhelper.h"
#include "Base/qbasetableview.h"

QFileNameItem::QFileNameItem(CFileNode *node, QWidget *parent)
	: QWidget(parent),
	m_fileNode(node)
{
	ui.setupUi(this);
	//m_parentWidget = static_cast<QBaseTableWidget *>(parent);
	m_parentWidget = static_cast<QBaseTableView *>(parent);
	m_lineEdit = ui.lineEdit;
	m_checkBox = ui.checkBox;
	setFocusPolicy(Qt::ClickFocus);
	//setWindowFlags(Qt::FramelessWindowHint);
	ui.checkBox->setStyleSheet("QCheckBox{background:transparent;}");
	ui.checkBox->setAttribute(Qt::WA_TranslucentBackground);
	ui.lblIcon->setAttribute(Qt::WA_TranslucentBackground);
	ui.lblName->setAttribute(Qt::WA_TranslucentBackground);
	//ui.btnDownload->setAttribute(Qt::WA_TranslucentBackground);
	//ui.btnSend->setAttribute(Qt::WA_TranslucentBackground);
	//ui.btnMore->setAttribute(Qt::WA_TranslucentBackground);
	
	QPixmap pixmap = QBaseFileIcon::getFileIconByExtension(m_fileNode->m_fileName, m_fileNode->m_bDir);
	ui.lblIcon->setPixmap(pixmap);

	//QString pixmap = CommonHelper::getIconBySuffix(fileName, bDir);
	//ui.lblIcon->setPixmap(QPixmap(pixmap));

	//ui.lblName->setText(m_fileNode->m_fileName);
	//QRect rect = ui.lblName->geometry();
	//m_lineEdit->setGeometry(rect.x(), rect.y(), rect.width() + 10, rect.height());
	//m_lineEdit->installEventFilter(this);
	//m_lineEdit->setText(ui.lblName->text());
	//showFileNameEdit();
	hideFileNameEdit();

	connect(m_lineEdit, &QLineEdit::returnPressed, [=](){
		m_fileNode->setFileName(m_lineEdit->text());
		setFileName(m_lineEdit->text());
		hideFileNameEdit();
	});

	connect(m_lineEdit, &QLineEdit::editingFinished, [=](){
		hideFileNameEdit();
	});

	connect(m_checkBox, &QCheckBox::clicked, [=](){
		emit sigSetChecked();
	});

	connect(ui.lblName, &QBaseLabel::click, [=](){
		if (m_fileNode->m_bDir){
			emit sigChangeDir(m_fileNode);
		}
	});
}

QFileNameItem::~QFileNameItem()
{
	
}

void QFileNameItem::showFileNameEdit()
{
	QRect rect = ui.lblName->geometry();
	m_lineEdit->setGeometry(rect.x(), rect.y(), rect.width() + 10, rect.height());
	m_lineEdit->setText(m_fileNode->m_fileName);
	m_lineEdit->show();
	ui.lblName->hide();
}

void QFileNameItem::hideFileNameEdit()
{
	m_lineEdit->hide();
	ui.lblName->setText(m_fileNode->m_fileName);
	ui.lblName->show();
}

void QFileNameItem::setFileName(QString fileName)
{
	if (fileName != m_fileNode->m_fileName){
		m_fileNode->m_fileName = fileName;
		//ui.lblName->setText(fileName);
		QPixmap pixmap = QBaseFileIcon::getFileIconByExtension(m_fileNode->m_fileName, m_fileNode->m_bDir);
		ui.lblIcon->setPixmap(pixmap);
		//QString pixmap = CommonHelper::getIconBySuffix(fileName, m_bDir);
		//ui.lblIcon->setPixmap(QPixmap(pixmap));
	}
}

void QFileNameItem::setToolButtonVisible(bool bShow)
{
	ui.btnDownload->setVisible(bShow);
	ui.btnSend->setVisible(bShow);
	ui.btnMore->setVisible(bShow);
}

//void QFileNameItem::setBackgroundColor(QColor color)
//{
//	QString strColor = QString("background:rgb(%1,%2,%3);")
//										.arg(color.red())
//										.arg(color.green())
//										.arg(color.blue());
//	setStyleSheet(strColor);
//}

//void QFileNameItem::mousePressEvent(QMouseEvent *event)
//{
	//if (event->button() == Qt::LeftButton){
		//emit clicked();
	//}
	//QWidget::mousePressEvent(event);
//}