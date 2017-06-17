#include "qbasebutton.h"

QBaseButton::QBaseButton(QWidget *parent)
	: QToolButton(parent)
{
	setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
}

QBaseButton::~QBaseButton()
{

}
