#include "qsortfiltermodel.h"
#include "Common/common.h"
#include "qtablemodel.h"
#include <QDebug>

QSortFilterModel::QSortFilterModel(QObject *parent)
	: QSortFilterProxyModel(parent),
	m_strCondition("")
{

}

QSortFilterModel::~QSortFilterModel()
{

}

void QSortFilterModel::setCondition(const QString &strCondition)
{
	m_strCondition = strCondition;
	invalidateFilter();
}

//bool QSortFilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
//{
//	QModelIndex index = sourceModel()->index(source_row, CHECK_BOX_COLUMN, source_parent);
//	QString fileName = sourceModel()->data(index, Qt::UserRole).toString();
//
//	if (fileName.indexOf(m_strCondition) == -1){
//		return false;
//	}
//	return true;
//}

bool QSortFilterModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
	if (!source_left.isValid() || !source_right.isValid())
		return false;

	int leftColumn = source_left.column();
	int rightColumn = source_right.column();
	if (leftColumn == CHECK_BOX_COLUMN && rightColumn == CHECK_BOX_COLUMN){
		QVariant leftData = sourceModel()->data(source_left, Qt::UserRole);
		QVariant rightData = sourceModel()->data(source_right, Qt::UserRole);

		CFileNode *leftNode = (CFileNode *)leftData.value<void *>();
		CFileNode *rightNode = (CFileNode *)rightData.value<void *>();

		bool left = leftNode->m_bDir;
		bool right = rightNode->m_bDir;

		qDebug() << leftNode->m_fileName << "," << rightNode->m_fileName;
		qDebug() << left << "," << right;
		if (left ^ right){
			return left;
		}
		
		QString strLeftData = leftNode->m_fileName;
		QString strRightData = rightNode->m_fileName;

		return strLeftData.compare(strRightData, Qt::CaseInsensitive) < 0;
	}else if (leftColumn == FILE_SIZE_COLUMN && rightColumn == FILE_SIZE_COLUMN){
		QVariant leftData = sourceModel()->data(sourceModel()->index(source_left.row(),CHECK_BOX_COLUMN), Qt::UserRole);
		QVariant rightData = sourceModel()->data(sourceModel()->index(source_right.row(), CHECK_BOX_COLUMN), Qt::UserRole);

		CFileNode *leftNode = (CFileNode *)leftData.value<void *>();
		CFileNode *rightNode = (CFileNode *)rightData.value<void *>();

		bool left = leftNode->m_bDir;
		bool right = rightNode->m_bDir;
		if (left ^ right){
			return left;
		}

		QVariant leftVar = sourceModel()->data(source_left, Qt::UserRole);
		QVariant rightVar = sourceModel()->data(source_right, Qt::UserRole);
		return leftVar.toLongLong() < rightVar.toLongLong();
	}else if (leftColumn == FILE_TIME_COLUMN && rightColumn == FILE_TIME_COLUMN){
		QVariant leftData = sourceModel()->data(source_left, Qt::UserRole);
		QVariant rightData = sourceModel()->data(source_right, Qt::UserRole);
		return leftData.toUInt() < rightData.toUInt();
	}
	return QSortFilterProxyModel::lessThan(source_left, source_right);
}

bool QSortFilterModel::isDir(const QModelIndex &index) const
{
	QTableModel *tableModel = static_cast<QTableModel*>(sourceModel());
	return tableModel->getFileNodes()->at(index.row())->m_bDir;
}