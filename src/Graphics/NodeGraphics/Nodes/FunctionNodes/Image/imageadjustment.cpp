#include "imageadjustment.h"

ImageAdjustment::ImageAdjustment(QPointF pos):Node(Node::FunctionNode, pos)
{
    NodeName="图像亮度对比度";
    //添加控制端口
    AddPort(new Port(0,"",Port::InStream,Port::Stream));
    AddPort(new Port(0,"",Port::OutStream,Port::Stream));

    //数据端口
    AddPort(new Port(1,"图像输入",Port::Input,Port::Image,QImage()));
    AddPort(new Port(1,"图像输出",Port::Output,Port::Image,QImage()));

    AddPort(new Port(2,"亮度",Port::Input,Port::Int,0));
    AddPort(new Port(3,"对比度",Port::Input,Port::Int,1));



    NodeHeight=300;
}

void ImageAdjustment::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Node::paint(painter,option,widget);
    // 检查图片是否有效，然后绘制它
    if (!Image.isNull()) {
        // 定义图片位置和大小
        QRectF imageRect(3, 200, 130, 130);

        // 绘制图片
        painter->drawImage(imageRect, Image);
    }


}

void ImageAdjustment::execute()
{
    QVariant imgval=GetPortValue(1,Port::Input);
    Image=imgval.value<QImage>();

    int width = Image.width();
    int height = Image.height();

    int brightness=GetPortValue(2,Port::Input).toInt();
    int contrast=GetPortValue(3,Port::Input).toInt();


    QImage outimg=Image;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            QColor color = Image.pixelColor(x, y);

            // 调整亮度
            int newRed = qBound(0, color.red() + brightness, 255);
            int newGreen = qBound(0, color.green() + brightness, 255);
            int newBlue = qBound(0, color.blue() + brightness, 255);

            // 调整对比度
            newRed = qBound(0, contrast * (newRed - 128) + 128, 255);
            newGreen = qBound(0, contrast * (newGreen - 128) + 128, 255);
            newBlue = qBound(0, contrast * (newBlue - 128) + 128, 255);

            outimg.setPixelColor(x, y, QColor(newRed, newGreen, newBlue));
        }
    }

    SetPortValue(1,outimg,Port::Output);
}
