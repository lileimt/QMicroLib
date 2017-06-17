#include "qbaselistitem.h"

QBaseListItem::QBaseListItem(QPixmap pixmap, QString strName, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	setFixedSize(150, 140);
	ui.lblIcon->setAttribute(Qt::WA_TranslucentBackground);
	ui.lblName->setAttribute(Qt::WA_TranslucentBackground);
	ui.edtName->setAttribute(Qt::WA_TranslucentBackground);
	ui.lblIcon->setGeometry(25, 20, 100, 90);
	ui.lblIcon->setPixmap(pixmap.scaled(ui.lblIcon->size()));
	ui.lblName->setGeometry(0, 115, 150, 20);
	ui.lblName->setAlignment(Qt::AlignHCenter);
	ui.lblName->setText(strName);
	ui.edtName->setGeometry(0, 115, 150, 20);
	ui.edtName->setAlignment(Qt::AlignHCenter);

	setWidgetVisible(true);

	setStyleSheet("QBaseListItem:hover{border:1px solid gray;background:skyblue; }");
}

QBaseListItem::~QBaseListItem()
{

}

void QBaseListItem::setWidgetVisible(bool bVisible)
{
	ui.lblName->setVisible(bVisible);
	if (!bVisible){
		ui.edtName->setText(ui.lblName->text());
	}
	ui.edtName->setVisible(!bVisible);
}

void QBaseListItem::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);

	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

	//QWidget::paintEvent(event);
}