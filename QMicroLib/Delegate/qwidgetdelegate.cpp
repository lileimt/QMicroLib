#include "qwidgetdelegate.h"
#include "FileNode.h"

QWidgetDelegate::QWidgetDelegate(QObject *parent)
	: QItemDelegate(parent)
{

}

QWidgetDelegate::~QWidgetDelegate()
{

}

QWidget *QWidgetDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QFileNameItem *widget = new QFileNameItem(new CFileNode(QStringLiteral("新建文件夹"),"","","","",true),parent);
	return widget;
}

void QWidgetDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	
}

void QWidgetDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

}

void QWidgetDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	editor->setGeometry(option.rect);
}
