#ifndef QBASEFILEICON_H
#define QBASEFILEICON_H

#include <QIcon>
#include <QDir>
#include <QFileInfo>
#include <QFileIconProvider>
#include <QTemporaryFile>
#include <QtWin>
#include <windows.h>
#include <iostream>

using namespace std;

class QBaseFileIcon
{
public:
	QBaseFileIcon();
	~QBaseFileIcon();

	static HICON getFolderIcon();
	static HICON getFileIcon(string extention);
	static QPixmap getFileIconByExtension(const QString &fileName, bool bDir = false);
private:
	
};

#endif // QBASEFILEICON_H
