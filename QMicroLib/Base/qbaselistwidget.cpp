#include "qbaselistwidget.h"

QBaseListWidget::QBaseListWidget(QWidget *parent)
	: QListWidget(parent)
{
	setViewMode(QListView::IconMode);
	setResizeMode(QListView::Adjust);
	setMovement(QListView::Static);
	setIconSize(QSize(iconWidth, iconHeight));
	//setEditTriggers(QAbstractItemView::AnyKeyPressed);
	setSpacing(10);

	setStyleSheet(
		"QListWidget::item{}"
		);
}

QBaseListWidget::~QBaseListWidget()
{

}

void QBaseListWidget::addItemIntoListWidget(QPixmap pixmap, QString text)
{
	QListWidgetItem *pItem = new QListWidgetItem(QIcon(pixmap.scaled(iconWidth, iconHeight)), text);
	pItem->setSizeHint(QSize(140,130));
	//pItem->setToolTip(text);
	addItem(pItem);
}