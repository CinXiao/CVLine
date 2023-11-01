#include "imageconversion.h"


ImageConversion::ImageConversion(QPointF pos):Node(Node::FunctionNode, pos)
{
    NodeName="图像转换";
    //添加控制端口
    AddPort(new Port(0,"",Port::InStream,Port::Stream));
    AddPort(new Port(0,"",Port::OutStream,Port::Stream));

    //数据端口
    AddPort(new Port(1,"图像输入",Port::Input,Port::Image,QImage()));

    AddPort(new Port(1,"ARGB",Port::Output,Port::Image,QImage()));
    AddPort(new Port(2,"Gray",Port::Output,Port::Image,QImage()));
    AddPort(new Port(3,"RGB",Port::Output,Port::Image,QImage()));
}

void ImageConversion::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    Node::paint(painter,option,widget);
    // 检查图片是否有效，然后绘制它
    if (!Image.isNull()) {
        // 定义图片位置和大小
        QRectF imageRect(3, 120, 80, 80);

        // 绘制图片
        painter->drawImage(imageRect, Image);
    }
}

void ImageConversion::execute()
{
    QVariant imgval=GetPortValue(1,Port::Input);
    Image=imgval.value<QImage>();

    // 转换为32位ARGB格式
    QImage argbImage = Image.convertToFormat(QImage::Format_ARGB32);
    // 转换为灰度图像
    QImage grayscaleImage = Image.convertToFormat(QImage::Format_Grayscale8);
    // 转换为RGB格式
    QImage rgbImage = Image.convertToFormat(QImage::Format_RGB32);




    SetPortValue(1,argbImage,Port::Output);
    SetPortValue(2,grayscaleImage,Port::Output);
    SetPortValue(3,rgbImage,Port::Output);


    Node::execute();

}
