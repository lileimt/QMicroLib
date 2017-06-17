#ifndef _STRUCT_H_
#define  _STRUCT_H_

#include <QString>

typedef struct {
	QString fileName;
	QString fileInfo1;
	QString fileInfo2;
	QString fileInfo3;
	bool bDir;
}FILE_INFO,*PFILE_INFO;

#endif