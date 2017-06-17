#ifndef QTABLEMODEL_H
#define QTABLEMODEL_H

#include <QAbstractTableModel>
#include "FileNode.h"

class QTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	QTableModel(QObject *parent = 0);
	~QTableModel();

	void setHorizontalHeaderList(QStringList horizontalHeaderList);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	//bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	Qt::ItemFlags flags(const QModelIndex &index);
	void setModelData(QList<CFileNode *> *childNodes);
	void refreshModel();
	void setHoverRow(int row);
	QList<CFileNode *> *getFileNodes();
signals:
	void updateCount(int count);

private:
	QStringList m_horizontalHeaderList;
	QList<CFileNode *> *m_childNodes;
	int m_hoverRow;
};

#endif // QTABLEMODEL_H
