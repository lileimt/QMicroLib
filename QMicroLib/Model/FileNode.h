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
	QString m_fileAuthor;  //提交者

	bool m_bStatus;    //提交状态
	bool m_bDir;  //是否为目录
	//bool m_hasChildDirs;    //是否有子目录

	CFileNode *m_parent;       //当前节点的父节点
	QList<CFileNode *> m_childNodes;    //当前节点的子节点
	
	void setFileName(QString fileName);
	void setParent(CFileNode *pNode);
	CFileNode *getParent();
	void setIsDir(bool bDir);
	void setFileSize(QString size);
	void setFileTime(QString time);

	void append(CFileNode *pNode);
	void insert(CFileNode *pNode);
};

