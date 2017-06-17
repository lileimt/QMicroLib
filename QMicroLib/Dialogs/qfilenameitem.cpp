#include "qfilenameitem.h"
#include "common/iconhelper.h"
#include "common/commonhelper.h"

QFileNameItem::QFileNameItem(CFileNode *node, QWidget *parent)
	: QWidget(parent),
	m_fileNode(node)
{
	ui.setupUi(this);
	//m_parentWidget = static_cast<QBaseTableWidget *>(parent);
	//m_parentWidget = static_cast<QBaseTableView *>(parent);
	m_lineEdit = ui.lineEdit;
	m_checkBox = ui.checkBox;
	//setWindowFlags(Qt::FramelessWindowHint);
	ui.checkBox->setStyleSheet("QCheckBox{background:transparent;}");
	ui.checkBox->setAttribute(Qt::WA_TranslucentBackground);
	ui.lblIcon->setAttribute(Qt::WA_TranslucentBackground);
	ui.lblName->setAttribute(Qt::WA_TranslucentBackground);
	//ui.btnDownload->setAttribute(Qt::WA_TranslucentBackground);
	//ui.btnSend->setAttribute(Qt::WA_TranslucentBackground);
	//ui.btnMore->setAttribute(Qt::WA_TranslucentBackground);

	//IconHelper::getInstance()->setIcon(ui.btnDownload, QChar(0xf063));
	//IconHelper::getInstance()->setIcon(ui.btnSend, QChar(0xf1d8));
	//IconHelper::getInstance()->setIcon(ui.btnMore, QChar(0xf067));
	
	QPixmap pixmap = QBaseFileIcon::getFileIconByExtension(m_fileNode->m_fileName, m_fileNode->m_bDir);
	ui.lblIcon->setPixmap(pixmap);

	//QString pixmap = CommonHelper::getIconBySuffix(fileName, bDir);
	//ui.lblIcon->setPixmap(QPixmap(pixmap));

	ui.lblName->setText(m_fileNode->m_fileName);
	//m_lineEdit = new QLineEdit(this);
	QRect rect = ui.lblName->geometry();
	m_lineEdit->setGeometry(rect.x(), rect.y(), rect.width() + 10, rect.height());
	//m_lineEdit->setText(ui.lblName->text());
	//showFileNameEdit();
	hideFileNameEdit();

	connect(m_lineEdit, &QLineEdit::returnPressed, [=](){
		setFileName(m_lineEdit->text());
		hideFileNameEdit();
	});

	connect(m_checkBox, &QCheckBox::clicked, [=](){
		//if (m_checkBox->checkState() == Qt::Checked){
		//	m_parentWidget->checkBoxSelectedCountIncrease();
		//}else{
		//	m_parentWidget->checkBoxSelectedCountDecrease();
		//}
		//m_parentWidget->setCheckBoxState();
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
	m_lineEdit->setText(ui.lblName->text());
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

void QFileNameItem::setBackgroundColor(QColor color)
{
	QString strColor = QString("background:rgb(%1,%2,%3);")
										.arg(color.red())
										.arg(color.green())
										.arg(color.blue());
	setStyleSheet(strColor);
}

// 解决setstylesheet不生效的问题
//void QFileNameItem::paintEvent(QPaintEvent *event)
//{
//	QStyleOption opt;
//	opt.init(this);
//
//	QPainter p(this);
//	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
//
//	//QWidget::paintEvent(event);
//}