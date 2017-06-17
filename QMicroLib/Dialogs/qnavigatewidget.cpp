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
		if (text == QStringLiteral("全部文档")){
			emit sigAllFiles();
		}else if (text == QStringLiteral("文档")){
			emit sigWord();
		}else if (text == QStringLiteral("表格")){
			emit sigExcel();
		}else if (text == QStringLiteral("幻灯片")){
			emit sigPPT();
		}else if (text == QStringLiteral("图片")){
			emit sigImage();
		}else if (text == QStringLiteral("影音")){
			emit sigMovie();
		}else if (text == QStringLiteral("其他")){
			emit sigOther();
		}else if (text == QStringLiteral("收到的文件")){
			emit sigRecvFiles();
		}else if (text == QStringLiteral("收集文件夹")){
			emit sigFolder();
		}else if (text == QStringLiteral("我的收藏")){
			emit sigMyCollect();
		}else if (text == QStringLiteral("我的提交")){
			emit sigMyCommit();
		}else if (text == QStringLiteral("操作历史")){
			emit sigHistory();
		}else if (text == QStringLiteral("回收站")){
			emit sigRecycelBin();
		}else{

		}
	});
}

QNavigateWidget::~QNavigateWidget()
{

}
