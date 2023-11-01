#include "getimageinfo.h"



GetImageInfo::GetImageInfo(QPointF pos):Node(Node::FunctionNode, pos)
{
    NodeName="获取图像信息";
    //添加控制端口
    AddPort(new Port(0,"",Port::InStream,Port::Stream));
    AddPort(new Port(0,"",Port::OutStream,Port::Stream));

    //数据端口
    AddPort(new Port(1,"图像输入",Port::Input,Port::Image,QImage()));

    AddPort(new Port(1,"图像输出",Port::Output,Port::Image,QImage()));
    AddPort(new Port(2,"W",Port::Output,Port::Int,0));
    AddPort(new Port(3,"H",Port::Output,Port::Int,0));


}

void GetImageInfo::execute()
{
    QVariant imgval=GetPortValue(1,Port::Input);
    QImage  img=imgval.value<QImage>();
    SetPortValue(1,img,Port::Output);

    SetPortValue(2,img.width(),Port::Output);
    SetPortValue(3,img.height(),Port::Output);

    Node::execute();
}

