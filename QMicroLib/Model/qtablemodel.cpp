#include "qtablemodel.h"
#include "Common/common.h"
#include <QDateTime>
#include <QDebug>

QString bytesToGMKB(qint64 size)
{
	if (size / GB >= 1)
		return QString("%1 GB").arg(QString::number(size / (float)GB, 'f', 2));
	else if (size / MB >= 1)
		return QString("%1 MB").arg(QString::number(size / (float)MB, 'f', 2));
	else if (size / KB >= 1)
		return QString("%1 KB").arg(QString::number(size / (float)KB, 'f', 2));
	else
		return QString("%1 Bytes").arg(size);
}

QTableModel::QTableModel(QObject *parent)
	: QAbstractTableModel(parent),
	m_childNodes(nullptr),
	m_hoverRow(-1)
{

}

QTableModel::~QTableModel()
{

}

void QTableModel::setHorizontalHeaderList(QStringList horizontalHeaderList)
{
	m_horizontalHeaderList = horizontalHeaderList;
}

int QTableModel::rowCount(const QModelIndex &parent) const
{
	if (m_childNodes == NULL)return 0;
	return m_childNodes->size();
}

int QTableModel::columnCount(const QModelIndex &parent) const
{
	return m_horizontalHeaderList.size();
}

QVariant QTableModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	int row = index.row();  //ÐÐºÅ
	if (row < 0 || row >= m_childNodes->size())
		return QVariant();

	int column = index.column();
	if (column<0 || column > m_horizontalHeaderList.size())
		return QVariant();

	switch (role){
		case Qt::BackgroundColorRole:
		{
				if (row == m_hoverRow){
					return QColor("lightblue");
				}
				break;
		}
		case Qt::DisplayRole:
		{
				CFileNode *node = m_childNodes->at(row);
				switch (column)
				{
				case CHECK_BOX_COLUMN:
					return "";
				case FILE_NAME_COLUMN:
					return node->m_fileName;
				case FILE_AUTHOR_CLOUMN:
					return node->m_fileAuthor;
				case FILE_SIZE_COLUMN:
					if (node->m_bDir){
						return "";
					}
					return bytesToGMKB(node->m_fileSize.toLongLong());
				case FILE_TIME_COLUMN:
					return node->m_fileTime;
				case FILE_PATH_COLUMN:
					return node->m_filePath;
				default:
					break;
				}
				break;
		}	
		case Qt::UserRole:
		{
				CFileNode *node = m_childNodes->at(row);
				if (column == CHECK_BOX_COLUMN){
					return QVariant::fromValue((void *)node);//node->m_fileName;
				}else if (column == FILE_SIZE_COLUMN){
					return node->m_fileSize.toLongLong();
				}else if (column == FILE_TIME_COLUMN){
					QDateTime time =  QDateTime::fromString(node->m_fileTime, "yyyy-MM-dd hh:mm");
					return time.toTime_t();
				}
				break;
		}
		default:
			break;
	}
	return QVariant();
}

QVariant QTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole){
		if (m_horizontalHeaderList.size() > section){
			return m_horizontalHeaderList[section];
		}
	}
	return QVariant();
}

Qt::ItemFlags QTableModel::flags(const QModelIndex &index)
{
	if (!index.isValid()){
		return Qt::NoItemFlags;
	}

	Qt::ItemFlags flag = QAbstractItemModel::flags(index);

	return flag;
}

void QTableModel::refreshModel()
{
	beginResetModel();
	endResetModel();

	emit updateCount(rowCount(QModelIndex()));
}

void QTableModel::setModelData(QList<CFileNode *> *childNodes)
{
	m_childNodes = childNodes;
}

void QTableModel::setHoverRow(int row)
{
	m_hoverRow = row;
}

QList<CFileNode *> *QTableModel::getFileNodes()
{
	return m_childNodes;
}