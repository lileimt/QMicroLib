#include "qtoolbarwidget.h"

QToolBarWidget::QToolBarWidget(QWidget *parent)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	//setAutoFillBackground(true);
	setStyleSheet("background:rgb(240,240,240);");
	//ui.btnUpload->setAttribute(Qt::WA_TranslucentBackground);
	ui.searchWidget->setStyleSheet("border:1px solid green;background:white;");
	ui.lineEdit->setStyleSheet("border:none;");
	ui.btnSearch->setStyleSheet("border:none;");

	connect(ui.btnUpload, SIGNAL(clicked()), this, SIGNAL(uploadClicked()));
	connect(ui.btnDownload, SIGNAL(clicked()), this, SIGNAL(downloadClicked()));
	connect(ui.btnDelete, SIGNAL(clicked()), this, SIGNAL(deleteClicked()));
	connect(ui.btnNew, SIGNAL(clicked()), this, SIGNAL(newFileClicked()));
	connect(ui.btnShare, SIGNAL(clicked()), this, SIGNAL(shareClicked()));
	connect(ui.btnMore, SIGNAL(clicked()), this, SIGNAL(moreClicked()));

	connect(ui.btnSearch, &QToolButton::clicked, [=](){
		QString text = ui.lineEdit->text();
		emit searchClicked(text);
	});
	connect(ui.lineEdit, &QLineEdit::returnPressed, [=](){
		QString text = ui.lineEdit->text();
		emit searchClicked(text);
	});
	connect(ui.lineEdit, &QLineEdit::textChanged, [=](const QString &text){
		if (text == ""){
			emit sigTextChanged(text);
		}
	});
}

QToolBarWidget::~QToolBarWidget()
{

}
