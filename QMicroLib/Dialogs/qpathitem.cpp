#include "qpathitem.h"
#include <QMouseEvent>

QPathItem::QPathItem(CFileNode *FileNode,bool bHome, QWidget *parent)
		: QBaseWidget(parent),
		m_FileNode(FileNode),
		//m_hasChildDirs(hasChildDirs),
		m_bHome(bHome),
		m_index(0)
{
	ui.setupUi(this);
	//setAttribute(Qt::WA_TranslucentBackground);
	setStyleSheet("border:none;");
	ui.lblPath->setAttribute(Qt::WA_TranslucentBackground);
	ui.lblPath->setText(FileNode->m_fileName);
	ui.lblPath->setStyleSheet("border:none;");
	if (!bHome){
		ui.btnHome->hide();
	}else{
		ui.btnHome->setStyleSheet("border-image:url(:/toolbar/home);");
	}
	if (!m_FileNode->m_bDir){
		ui.btnTriangle->hide();
	}else{
		ui.btnTriangle->setStyleSheet("border-image:url(:/toolbar/right);");
	}
	ui.lblPath->installEventFilter(this);
}

QPathItem::~QPathItem()
{

}

void QPathItem::enterEvent(QEvent *event)
{
	Q_UNUSED(event);
	setCursor(Qt::PointingHandCursor);
	ui.lblPath->setStyleSheet("text-decoration:underline;color:blue;");
	if (m_bHome){
		ui.btnHome->setStyleSheet("border-image:url(:/toolbar/home_hover);");
	}
	if (m_FileNode->m_bDir){
		ui.btnTriangle->setStyleSheet("border-image:url(:/toolbar/right_hover);");
	}
}

void QPathItem::leaveEvent(QEvent *event)
{
	Q_UNUSED(event);
	setCursor(Qt::ArrowCursor);
	ui.lblPath->setStyleSheet("text-decoration:none;");
	if (m_bHome){
		ui.btnHome->setStyleSheet("border-image:url(:/toolbar/home);");
	}
	if (m_FileNode->m_bDir){
		ui.btnTriangle->setStyleSheet("border-image:url(:/toolbar/right);");
	}
}

int QPathItem::getWidth()
{
	return width();
}

void QPathItem::setIndex(int index)
{
	m_index = index;
}

int QPathItem::getIndex()
{
	return m_index;
}

bool QPathItem::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == ui.lblPath){
		if (event->type() == QEvent::MouseButtonPress){
			QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
			if (mouseEvent->button() == Qt::LeftButton){
				emit sigClicked(m_index);
			}
		}
	}

	return QWidget::eventFilter(watched, event);
}

CFileNode *QPathItem::getCurNode()
{
	return m_FileNode;
}