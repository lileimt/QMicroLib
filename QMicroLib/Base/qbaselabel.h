#ifndef QBASELABEL_H
#define QBASELABEL_H

#include <QLabel>
#include <QEvent>
#include <QMouseEvent>

class QBaseLabel : public QLabel
{
	Q_OBJECT

public:
	QBaseLabel(QWidget *parent=0);
	~QBaseLabel();

	void setHoverColor(bool bHoverColor);
	void setText(const QString &string);
	int getWidth();
protected:
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);
	void mousePressEvent(QMouseEvent *ev);

signals:
	void click();
private:
	bool m_bHoverColor;
	int m_length;
	QString m_string;
};

#endif // QBASELABEL_H
