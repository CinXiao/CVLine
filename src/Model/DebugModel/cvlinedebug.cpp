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

void CVLineDebug::print(QString infotext, InfoType infotype)
{

    QString info;
    if(infotype==Info)
    {

        info=QString("<span style=\"background-color: darkgreen;color:white \">%1 信息: %2</span>")
                   .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
            .arg(infotext);
    }else if(infotype==Normal)
    {

        info=QString("<span style=\"background-color: gray;color:black\">%1 %2</span>")
                   .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                   .arg(infotext);
    }else if(infotype==Warning)
    {

        info=QString("<span style=\"background-color: darkorange;color:white\">%1 警告: %2</span>")
                   .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                   .arg(infotext);
    }else if(infotype==Errer)
    {

        info=QString("<span style=\"background-color: darkred;color:white\">%1 错误: %2</span>")
                   .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                   .arg(infotext);
    }
    emit  getInstance()->Debug(info);
}
