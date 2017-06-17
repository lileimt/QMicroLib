#include "qbaselabel.h"

QBaseLabel::QBaseLabel(QWidget *parent)
	: QLabel(parent),
	m_bHoverColor(false)
{
}

QBaseLabel::~QBaseLabel()
{
}

void QBaseLabel::enterEvent(QEvent *event)
{
	Q_UNUSED(event);
	setCursor(Qt::PointingHandCursor);
	if (!m_bHoverColor){
		setToolTip(text());
		setStyleSheet("text-decoration:underline;");
	}else{
		setStyleSheet("text-decoration:underline;color:blue;");
	}
}

void QBaseLabel::leaveEvent(QEvent *event)
{
	Q_UNUSED(event);
	setCursor(Qt::ArrowCursor);
	setStyleSheet("text-decoration:none;");
}

void QBaseLabel::setHoverColor(bool bHoverColor)
{
	m_bHoverColor = bHoverColor;
}

void QBaseLabel::mousePressEvent(QMouseEvent *ev)
{
	if (ev->button() == Qt::LeftButton){
		emit click();
	}
}