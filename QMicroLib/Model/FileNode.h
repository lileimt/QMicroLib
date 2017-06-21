#pragma once

#include <QString>
#include <QPixmap>
#include <QList>

class CFileNode
{
public:
	CFileNode();
	CFileNode(QString fileName, QString fileSize = "", QString fileTime = "", QString filePath = "", QString fileAuthor = "", bool bDir = false, bool bStatus = false/*, bool hasChildDirs = false*/);
	~CFileNode();

	QString m_fileName;
	QPixmap m_fileIcon;
	QString m_fileSize;
	//qint64   m_fileSize;
	QString m_fileTime;
	QString m_filePath;
	QString m_fileAuthor;  //�ύ��

	bool m_bStatus;    //�ύ״̬
	bool m_bDir;  //�Ƿ�ΪĿ¼
	//bool m_hasChildDirs;    //�Ƿ�����Ŀ¼

	CFileNode *m_parent;       //��ǰ�ڵ�ĸ��ڵ�
	QList<CFileNode *> m_childNodes;    //��ǰ�ڵ���ӽڵ�
	
	void setFileName(QString fileName);
	void setParent(CFileNode *pNode);
	CFileNode *getParent();
	void setIsDir(bool bDir);
	void setFileSize(QString size);
	void setFileTime(QString time);

	void append(CFileNode *pNode);
	void insert(CFileNode *pNode);
};

