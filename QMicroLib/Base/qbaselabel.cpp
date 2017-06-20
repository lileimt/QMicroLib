#include "qbaselabel.h"
#include <QDebug>

QBaseLabel::QBaseLabel(QWidget *parent)
	: QLabel(parent),
	//m_bHoverColor(false),
	m_length(0)
{
	setStyleSheet("background:blue");
}

QBaseLabel::~QBaseLabel()
{
}

void QBaseLabel::enterEvent(QEvent *event)
{
	Q_UNUSED(event);
	setCursor(Qt::PointingHandCursor);
	//if (!m_bHoverColor){
		setToolTip(m_string);
		//setStyleSheet("text-decoration:underline;");
	//}else{
		//setStyleSheet("text-decoration:underline;color:blue;");
	//}
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

void QBaseLabel::setText(const QString &string)
{
	m_string = string;
	m_length = getWidth(m_string);
	QString str = string;
	QFontMetrics fontMetrics(font());
	int width = this->width();
	if (m_length > width){
		m_length = width;
		str = fontMetrics.elidedText(string, Qt::ElideRight, this->width());
	}
	QLabel::setText(str);
}

int QBaseLabel::getWidth(QString string)
{
	QFontMetrics fontMetrics(font());
	int length = fontMetrics.width(string);
	return length;
}