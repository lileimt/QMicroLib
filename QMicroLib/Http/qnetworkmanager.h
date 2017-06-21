#ifndef QNETWORKMANAGER_H
#define QNETWORKMANAGER_H

#include <QThread>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

class QNetWorkManager : public QThread
{
	Q_OBJECT

public:
	QNetWorkManager(QObject *parent);
	~QNetWorkManager();

public slots:

private:
	
};

#endif // QNETWORKMANAGER_H
