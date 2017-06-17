#include "qnavigatewidget.h"
#include <QDebug>

QNavigateWidget::QNavigateWidget(QWidget *parent)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	setStyleSheet("border:1px solid grey");
	ui.treeWidget->setStyleSheet("QTreeWidget{border:none}"
												  "QTreeWidget::item{height:25px}");
	ui.treeWidget->header()->hide();
	ui.treeWidget->expandAll();
	ui.treeWidget->setRootIsDecorated(false);

	connect(ui.treeWidget, &QTreeWidget::itemClicked, [=](QTreeWidgetItem *item, int column){
		QString text = item->text(0);
		qDebug() << text;
		if (text == QStringLiteral("ȫ���ĵ�")){
			emit sigAllFiles();
		}else if (text == QStringLiteral("�ĵ�")){
			emit sigWord();
		}else if (text == QStringLiteral("���")){
			emit sigExcel();
		}else if (text == QStringLiteral("�õ�Ƭ")){
			emit sigPPT();
		}else if (text == QStringLiteral("ͼƬ")){
			emit sigImage();
		}else if (text == QStringLiteral("Ӱ��")){
			emit sigMovie();
		}else if (text == QStringLiteral("����")){
			emit sigOther();
		}else if (text == QStringLiteral("�յ����ļ�")){
			emit sigRecvFiles();
		}else if (text == QStringLiteral("�ռ��ļ���")){
			emit sigFolder();
		}else if (text == QStringLiteral("�ҵ��ղ�")){
			emit sigMyCollect();
		}else if (text == QStringLiteral("�ҵ��ύ")){
			emit sigMyCommit();
		}else if (text == QStringLiteral("������ʷ")){
			emit sigHistory();
		}else if (text == QStringLiteral("����վ")){
			emit sigRecycelBin();
		}else{

		}
	});
}

QNavigateWidget::~QNavigateWidget()
{

}
