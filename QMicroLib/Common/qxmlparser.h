#ifndef QXMLPARSER_H
#define QXMLPARSER_H

#include <QObject>
#include <QtXML>
#include "Model/FileNode.h"

class QXMLParser : public QObject
{
	Q_OBJECT

public:
	QXMLParser(QObject *parent = 0);
	~QXMLParser();

	void openXML(QString fileName);
	void xmlParser(QDomElement &docElem, CFileNode *pNode);
	CFileNode *getFileNode();
private:
	CFileNode *m_pNode;
};

#endif // QXMLPARSER_H
