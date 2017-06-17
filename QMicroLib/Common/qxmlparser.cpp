#include "qxmlparser.h"

QXMLParser::QXMLParser(QObject *parent)
	: QObject(parent)
{
	m_pNode = new CFileNode;
}

QXMLParser::~QXMLParser()
{

}

void QXMLParser::openXML(QString fileName)
{
	QFile file(fileName);
	if (file.open(QIODevice::ReadOnly)){
		QDomDocument dom;
		if (dom.setContent(&file)){
			QDomElement docElem = dom.documentElement();
			xmlParser(docElem, m_pNode);
		}
	}
	file.close();
}

void QXMLParser::xmlParser(QDomElement &docElem, CFileNode *pNode)
{
	QDomNode node = docElem.firstChild();
	while (!node.isNull()){
		QDomElement element = node.toElement();
		if (!element.isNull()){
			qDebug() << element.tagName();
			CFileNode *childFileNode = new CFileNode;
			if (element.tagName() == "folder"){
				childFileNode->setFileName(element.attribute("name"));
				childFileNode->setIsDir(true);
				childFileNode->setFileTime(element.attribute("time"));
				xmlParser(element, childFileNode);
				pNode->append(childFileNode);
			}else if (element.tagName() == "file"){
				QDomNodeList nodeList = element.childNodes();
				qDebug() << nodeList.size();
				for (int i = 0; i < nodeList.size(); i++){
					QDomNode childNode = nodeList.item(i);
					QDomElement childElem = childNode.toElement();
					qDebug() << childElem.tagName()<<" "<<childElem.text();
					if (childElem.tagName() == "filename"){
						childFileNode->setFileName(childElem.text());
					}else if (childElem.tagName() == "size"){
						childFileNode->setFileSize(childElem.text());
					}else if (childElem.tagName() == "lastModified"){
						childFileNode->setFileTime(childElem.text());
					}
				}
				pNode->append(childFileNode);
			}
		}
		node = node.nextSibling();
	}
}

CFileNode *QXMLParser::getFileNode()
{
	return m_pNode;
}