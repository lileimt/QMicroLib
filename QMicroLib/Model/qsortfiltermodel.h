#ifndef QSORTFILTERMODEL_H
#define QSORTFILTERMODEL_H

#include <QSortFilterProxyModel>

class QSortFilterModel : public QSortFilterProxyModel
{
	Q_OBJECT

public:
	QSortFilterModel(QObject *parent = 0);
	~QSortFilterModel();

	bool isDir(const QModelIndex &index = QModelIndex()) const;
	void setCondition(const QString &strCondition);
protected:
	bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const;
	//bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
private:
	QString m_strCondition;
};

#endif // QSORTFILTERMODEL_H
