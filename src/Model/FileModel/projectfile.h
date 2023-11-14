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
    static GraphicsView *OpenProject(QUrl fileurl);

    inline static QMap<QString,std::function<Node*(QPointF)>> NodeMap{
        {"开始", [](QPointF pos) { return new StartNode(pos); }},
        {"IF", [](QPointF pos) { return new If(pos); }},
        {"Then", [](QPointF pos) { return new Then(pos); }},

        {"打印输出",  [](QPointF pos) { return new Print(pos); }},

        {"选择图像", [](QPointF pos) { return new ImageNode(pos); }},
        {"选择目录图像", [](QPointF pos) { return new ReadImage(pos); }},
        {"获取图像信息", [](QPointF pos) { return new GetImageInfo(pos); }},
        {"图像调整", [](QPointF pos) { return new ImageAdjustment(pos); }},
        { "二值化", [](QPointF pos) { return new Binarization(pos); }},
        {"通道分离", [](QPointF pos) { return new ChannelSeparation(pos); }},
        {"通道合并", [](QPointF pos) { return new ChannelMerging(pos); }},
        {"图像转换", [](QPointF pos) { return new ImageConversion(pos); }},
        {"高斯模糊", [](QPointF pos) { return new GaussianBlur(pos); }},

        {"整数", [](QPointF pos) { return new DataNode(pos, 0, Port::Int); }},
        {"小数", [](QPointF pos) { return new DataNode(pos, 0.0, Port::Double); }},
        {"布尔", [](QPointF pos) { return new DataNode(pos, false, Port::Bool); }},
        {"比特", [](QPointF pos) { return new DataNode(pos, 0, Port::Bit); }},
        {"字符串", [](QPointF pos) { return new DataNode(pos, "", Port::String); }},


        {"整数加", [](QPointF pos) { return new AddNode(pos,Port::Int); }},
        {"整数减", [](QPointF pos) { return new Subtract(pos,Port::Int); }},
        {"整数乘", [](QPointF pos) { return new Multiply(pos,Port::Int); }},
        {"整数除", [](QPointF pos) { return new Division(pos,Port::Int); }},
        {"整数取模", [](QPointF pos) { return new Mod(pos,Port::Int); }},
        {"整数Max", [](QPointF pos) { return new Max(pos,Port::Int); }},
        {"整数Min", [](QPointF pos) { return new Min(pos,Port::Int); }},


        {"小数加", [](QPointF pos) { return new AddNode(pos,Port::Double); }},
        {"小数减", [](QPointF pos) { return new Subtract(pos,Port::Double); }},
        {"小数乘", [](QPointF pos) { return new Multiply(pos,Port::Double); }},
        {"小数除", [](QPointF pos) { return new Division(pos,Port::Double); }},
        {"小数取模", [](QPointF pos) { return new Mod(pos,Port::Double); }},
        {"小数Max", [](QPointF pos) { return new Max(pos,Port::Double); }},
        {"小数Min", [](QPointF pos) { return new Min(pos,Port::Double); }},




    };



};

#endif // PROJECTFILE_H
