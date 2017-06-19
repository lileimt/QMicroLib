#include "qmicrolib.h"
#include <QtWidgets/QApplication>
#include "Common/commonhelper.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//CommonHelper::setStyle(":/qss/skin");
	CommonHelper::setStyle("Resources/qss/skin.css");

	QMicroLib w;
	w.show();
	return a.exec();
}
