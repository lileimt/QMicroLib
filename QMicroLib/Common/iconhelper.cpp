#include "iconhelper.h"

IconHelper *IconHelper::m_pInstance = NULL;

IconHelper::IconHelper(QObject *parent) : QObject(parent)
{
    int fontId = QFontDatabase::addApplicationFont(":/font/font");
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    iconFont = QFont(fontName);
}

void IconHelper::setIcon(QLabel *label, QChar chr, int size)
{
    iconFont.setPointSize(size);
    label->setFont(iconFont);
    label->setText(chr);
}

void IconHelper::setIcon(QToolButton *btn, QChar chr, int size)
{
    iconFont.setPixelSize(size);
    btn->setFont(iconFont);
    btn->setText(chr);
}

void IconHelper::setIcon(QPushButton *btn, QChar chr, int size)
{
    iconFont.setPixelSize(size);
    btn->setFont(iconFont);
    btn->setText(chr);
}
