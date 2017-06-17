#ifndef ICONHELPER_H
#define ICONHELPER_H

#include <QFont>
#include <QChar>
#include <QLabel>
#include <QMutex>
#include <QObject>
#include <QToolButton>
#include <QPushButton>
#include <QMutexLocker>
#include <QFontDatabase>

const QChar home = 0xf015;             //��ҳ
const QChar arrowLeft = 0xf060;       //���ͷ
const QChar carretRight = 0xf0da;    //��������
const QChar carretDown = 0Xf0d7;   //��������
const QChar refresh = 0xf021;          //ˢ��
const QChar retweet = 0xf079;         //�л�
const QChar detailview = 0xf00b;     //�б���ͼ
const QChar tilteview = 0xf009;        //ƽ����ͼ

class IconHelper : public QObject
{
    Q_OBJECT
private:
    IconHelper(QObject *parent = 0);
    QFont iconFont;
    static IconHelper *m_pInstance;
public:
    static IconHelper *getInstance(){
        static QMutex mutex;
        if(!m_pInstance){
            QMutexLocker locker(&mutex);
            if(!m_pInstance){
                m_pInstance = new IconHelper;
            }
        }
        return m_pInstance;
    }

    void setIcon(QLabel *label,QChar chr,int size = 16);
    void setIcon(QToolButton *btn,QChar chr,int size = 16);
    void setIcon(QPushButton *btn,QChar chr,int size = 16);
};

#endif // ICONHELPER_H
