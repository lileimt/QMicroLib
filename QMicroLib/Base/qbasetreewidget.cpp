#include "qbasetreewidget.h"

QBaseTreeWidget::QBaseTreeWidget(QWidget *parent)
	: QTreeWidget(parent)
{
	setHeaderLabels(QStringList() << "Key" << "Value");
}

QBaseTreeWidget::~QBaseTreeWidget()
{

}
