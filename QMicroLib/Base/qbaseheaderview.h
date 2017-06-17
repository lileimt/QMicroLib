#ifndef QBASEHEADERVIEW_H
#define QBASEHEADERVIEW_H

#include <QHeaderView>
#include <QPainter>
#include <QCheckBox>
#include <QMouseEvent>

class QBaseHeaderView : public QHeaderView
{
	Q_OBJECT

public:
	QBaseHeaderView(Qt::Orientation orientation, QWidget *parent = 0);
	~QBaseHeaderView();

	void setCheckBoxState(bool bChecked);
protected:
	void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
	void mouseMoveEvent(QMouseEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);

signals:
	void headerEntered();
	void stateChanged(bool bChecked);

private:
	bool m_bPressed;
	bool m_bChecked;
	QRect m_rect;
};

#endif // QBASEHEADERVIEW_H
