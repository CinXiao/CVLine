#ifndef PROJECTFILE_H
#define PROJECTFILE_H

#include <QUrl>
#include<QJsonArray>
#include<QJsonObject>
#include "src/Graphics/graphicsview.h"
#include<QJsonDocument>


class ProjectFile
{
public:
    ProjectFile();

    //保存项目文件
    static void SaveProjct(GraphicsView *view, QUrl url);


};

#endif // PROJECTFILE_H
