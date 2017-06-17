#include "qbasefileicon.h"

QBaseFileIcon::QBaseFileIcon()
{

}

QBaseFileIcon::~QBaseFileIcon()
{

}

HICON QBaseFileIcon::getFolderIcon()
{
	string str = "folder";
	LPCSTR name = str.c_str();
	
	HICON icon = NULL;
	SHFILEINFOA info;
	if (SHGetFileInfoA(name,
		FILE_ATTRIBUTE_DIRECTORY,
		&info,
		sizeof(info),
		SHGFI_SYSICONINDEX | SHGFI_ICON | SHGFI_USEFILEATTRIBUTES)){
		icon = info.hIcon;
	}
	return icon;
}

HICON QBaseFileIcon::getFileIcon(string extention)
{
	HICON icon = NULL;
	if (extention.length() > 0){
		LPCSTR name = extention.c_str();
		SHFILEINFOA info;
		if (SHGetFileInfoA(name,
			FILE_ATTRIBUTE_NORMAL,
			&info,
			sizeof(info),
			SHGFI_SYSICONINDEX | SHGFI_ICON | SHGFI_USEFILEATTRIBUTES)){
			icon = info.hIcon;
		}
	}
	return icon;
}

QPixmap QBaseFileIcon::getFileIconByExtension(const QString &fileName, bool bDir)
{
	QPixmap pixmap;
	if (bDir){
		pixmap = QtWin::fromHICON(getFolderIcon());
	}else{
		pixmap = QtWin::fromHICON(getFileIcon(fileName.toStdString()));
	}
	return pixmap;
}