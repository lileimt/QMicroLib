#include "FileNode.h"
#include "common/commonhelper.h"

CFileNode::CFileNode()
	:m_parent(NULL),
	m_bDir(false)
{

}

CFileNode::CFileNode(QString fileName, QString fileSize, QString fileTime, QString filePath, QString fileAuthor, bool bDir, bool bStatus/*, bool hasChildDirs*/)
				:m_fileName(fileName),
				m_fileSize(fileSize),
				m_fileTime(fileTime),
				m_filePath(filePath),
				m_fileAuthor(fileAuthor),
				m_bStatus(bStatus),
				m_bDir(bDir),
				//m_hasChildDirs(hasChildDirs),
				m_parent(NULL)
{
	m_fileIcon = QPixmap(CommonHelper::getIconBySuffix(fileName, m_bDir));
}


CFileNode::~CFileNode()
{
}

void CFileNode::setIsDir(bool bDir)
{
	m_bDir = bDir;
}

void CFileNode::setFileName(QString fileName)
{
	if (fileName != m_fileName){
		m_fileName = fileName;
	}
}

void CFileNode::setFileSize(QString size)
{
	m_fileSize = size;
}

void CFileNode::setFileTime(QString time)
{
	m_fileTime = time;
}

void CFileNode::append(CFileNode *pNode)
{
	m_childNodes.append(pNode);
	pNode->m_parent = this;
}

void CFileNode::insert(CFileNode *pNode)
{
	pNode->m_parent = this;
	m_childNodes.insert(0, pNode);
}

void CFileNode::setParent(CFileNode *pNode)
{
	m_parent = pNode;
}

CFileNode *CFileNode::getParent()
{
	return m_parent;
}