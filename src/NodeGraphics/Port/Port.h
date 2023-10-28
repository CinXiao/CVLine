#ifndef PORT_H
#define PORT_H

#include<QMap>
#include <QPainter>
#include <QGraphicsItem>

class Port
{
public:
    //端口类型
    enum PortType { None,InStream,OutStream, Input, Output };
    //端口数据类型
    enum PortDataType {Stream,Int, Bool,Float,String,Double,Vector2,Vector3,Color,Array};


    bool IsValid()
    {
        return portType!=None;
    }
    Port():portType(None)
    {

    }
    Port(uint id,QString Name="Port",PortType type=Input,PortDataType portDataType=Int,QVariant Data=0)
        :portType(type),
        ID(id),
        Name(Name),
        Data(Data),
        portDataType(portDataType),
        portColor(PortColorMap[portDataType])
    {
        if(portType==Input||portType==Output)
        {
            //设置端口颜色范围和端口文字范围和文字对齐方向
            portRect=(portType==Input)?QRectF(1,28+ID*30,20,20):QRectF(129,28+ID*30,20,20);
            portTextRect=(portType==Input)?QRectF(25,28+ID*28,50,28):QRectF(75,28+ID*28,50,28);
            TextAlign=(portType==Input)?Qt::AlignLeft:Qt::AlignRight;
        }
        else if(portType==InStream||portType==OutStream)
        {
            //设置端口颜色范围和端口文字范围和文字对齐方向
            portRect=(portType==InStream)?QRectF(2,3,15,15):QRectF(133,3,15,15);
        }


    }

    //端口类型是否可以连接判断
    bool PortEnableConnectCheck(PortType traporttype)
    {
        if(traporttype==InStream)
            return portType==OutStream;
        if(traporttype==OutStream)
            return portType==InStream;
        if(traporttype==Input)
            return portType==Output;
        if(traporttype==Output)
            return portType==Input;

        return portType==OutStream;
    }

    //端口存放的数据
    QVariant Data{0};
    //端口类型
    PortType portType;
    //端口数据类型
    PortDataType portDataType;
    //端口ID
    uint ID=0 ;
    //端口名称
    QString Name{"Port"};
    //端口范围
    QRectF portRect;
    //端口文字范围
    QRectF portTextRect;
    //端口文字对齐
    Qt::AlignmentFlag TextAlign;

    //端口颜色
    QColor portColor;

    //是否连接
    bool IsConnected=false;


    //端口数据类型颜色表
    inline static QMap<PortDataType,QColor> PortColorMap
    {
      {Stream,QColor(240,240,240)},
      {Int,QColor(106,34,136)},
      {Bool,QColor(136,34,34)},
      {Float,QColor(34, 136, 150)},
      {String,QColor(56,136,34)},
      {Double, QColor(34, 136, 204)},
      {Vector2, QColor(136, 84, 68)},
      {Vector3, QColor(136, 34, 68)},
      {Color, QColor(85, 34, 136)},
      {Array, QColor(68, 136, 34)}
    };


};







#endif // PORT_H
