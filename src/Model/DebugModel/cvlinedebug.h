#ifndef CVLINEDEBUG_H
#define CVLINEDEBUG_H

#include <QObject>

class CVLineDebug : public QObject
{

    Q_OBJECT

 public:

    enum InfoType
     {
         Normal,
         Info,
         Warning,
         Errer,
     };


    // 获取单例的静态方法
    static CVLineDebug* getInstance(QObject *parent = nullptr);
    static void print(QString infotext, InfoType infotype=Info);

signals:
    void Debug(QString infoText);

private:
    CVLineDebug(QObject *parent);
    static CVLineDebug* instance;
};

#endif // CVLINEDEBUG_H
