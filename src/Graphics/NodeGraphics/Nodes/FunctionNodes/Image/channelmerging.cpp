#include "channelmerging.h"

ChannelMerging::ChannelMerging(QPointF pos):Node(Node::FunctionNode, pos)
{
    NodeName="通道合并";
//    //添加控制端口
    AddPort(new Port(0,"",Port::InStream,Port::Stream));
    AddPort(new Port(0,"",Port::OutStream,Port::Stream));

//    //数据端口
    AddPort(new Port(1,"红色通道",Port::Input,Port::Image,QImage()));
    AddPort(new Port(2,"绿色通道",Port::Input,Port::Image,QImage()));
    AddPort(new Port(3,"蓝色通道",Port::Input,Port::Image,QImage()));

    AddPort(new Port(1,"合成输出",Port::Output,Port::Image,QImage()));

    NodeHeight=400;

}

void ChannelMerging::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    Node::paint(painter,option,widget);
    // 检查图片是否有效，然后绘制它
    if (!redImage.isNull())
        painter->drawImage(QRectF(3, 210, 60, 60), redImage);
    if (!greenImage.isNull())
    painter->drawImage(QRectF(3, 272, 60, 60), greenImage);
    if (!blueImage.isNull())
    painter->drawImage(QRectF(3, 332, 60, 60), blueImage);

}

void ChannelMerging::execute()
{
    QVariant imgval1=GetPortValue(1,Port::Input);
    redImage=imgval1.value<QImage>();

    QVariant imgval2=GetPortValue(2,Port::Input);

    greenImage=imgval2.value<QImage>();

    QVariant imgval3=GetPortValue(3,Port::Input);
    blueImage=imgval3.value<QImage>();

    QImage mergedImage(redImage.size(),redImage.format());

        QImage redChannel1 = redImage.copy(0, 0, redImage.width(), redImage.height());
        QImage greenChannel2 = greenImage.copy(0, 0, greenImage.width(), greenImage.height());
        QImage blueChannel3 = blueImage.copy(0, 0, blueImage.width(), blueImage.height());

        for (int x = 0; x < redImage.width(); x++) {
            for (int y = 0; y < redImage.height(); y++) {
                QRgb red = qRed(redChannel1.pixel(x, y));
                QRgb green = qGreen(greenChannel2.pixel(x, y));
                QRgb blue = qBlue(blueChannel3.pixel(x, y));
                // 合并三个通道
                QRgb mergedPixel = qRgb(red, green, blue);
                mergedImage.setPixel(x, y, mergedPixel);
            }
        }
         SetPortValue(1,mergedImage,Port::Output);

    Node::execute();
}
