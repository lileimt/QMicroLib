#include "qbaseheaderview.h"
#include "Common/common.h"
#include <QDebug>

QBaseHeaderView::QBaseHeaderView(Qt::Orientation orientation, QWidget *parent)
		: QHeaderView(orientation,parent),
		m_bPressed(false),
		m_bChecked(false),
		m_rect(6, 3, 20, 20)
{
	setStretchLastSection(true);
	setHighlightSections(false);
	setMouseTracking(true);
	setSectionsClickable(true);
	setDefaultSectionSize(150);
	setDefaultAlignment(Qt::AlignLeft);
	setFixedHeight(25);
}

QBaseHeaderView::~QBaseHeaderView()
{

}

void QBaseHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
	painter->save();
	QHeaderView::paintSection(painter, rect, logicalIndex);
	painter->restore();

	if (logicalIndex == CHECK_BOX_COLUMN){
		QStyleOptionButton option;
		option.initFrom(this);

		option.state |= m_bChecked ? QStyle::State_On : QStyle::State_Off;

		QCheckBox chkBox;
		option.iconSize = QSize(20, 20);
		option.rect = m_rect;
		style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter, &chkBox);

		QStyleOptionViewItem optionText;
		optionText.displayAlignment = Qt::AlignVCenter;
		optionText.initFrom(this);
		optionText.rect = rect;
		optionText.rect.setX(30);
		style()->drawItemText(painter, optionText.rect, optionText.displayAlignment, palette(), true, QStringLiteral("ÎÄ¼þÃû"));
	}
}

void QBaseHeaderView::mouseMoveEvent(QMouseEvent *e)
{
	emit headerEntered();
	return QHeaderView::mouseMoveEvent(e);
}

void QBaseHeaderView::mousePressEvent(QMouseEvent *e)
{
	int nColumn = logicalIndexAt(e->pos());
	if ((e->buttons() & Qt::LeftButton) && (nColumn == CHECK_BOX_COLUMN) && m_rect.contains(e->pos())){
		m_bPressed = true;
	}else{
		QHeaderView::mousePressEvent(e);
	}
}

void QBaseHeaderView::mouseReleaseEvent(QMouseEvent *e)
{
	if (m_bPressed){
		m_bChecked = !m_bChecked;
		update();

		emit stateChanged(m_bChecked);
	}else{
		QHeaderView::mouseReleaseEvent(e);
	}
	m_bPressed = false;
}

void QBaseHeaderView::setCheckBoxState(bool bChecked)
{
	m_bChecked = bChecked;
	update();
}