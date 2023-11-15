#include "cvlinedebug.h"

#include <QDateTime>

// 初始化静态成员变量为nullptr
CVLineDebug* CVLineDebug::instance = nullptr;

CVLineDebug::CVLineDebug(QObject *parent) : QObject(parent)
{
    // 私有构造函数
}

CVLineDebug* CVLineDebug::getInstance(QObject *parent)
{
    if (!instance)
    {
        instance = new CVLineDebug(parent);
    }

    return instance;
}

void CVLineDebug::print(QString infotext)
{

    QString info;


        info=QString("%1 : %2")
                   .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                   .arg(infotext);

    emit  getInstance()->Debug(info);
}
