#include "channelseparation.h"


ChannelSeparation::ChannelSeparation(QPointF pos):Node(Node::FunctionNode, pos)
{
    NodeName="通道分离";
    //添加控制端口
    AddPort(new Port(0,"",Port::InStream,Port::Stream));
    AddPort(new Port(0,"",Port::OutStream,Port::Stream));

    //数据端口
    AddPort(new Port(1,"图像输入",Port::Input,Port::Image,QImage()));

    AddPort(new Port(1,"红色通道",Port::Output,Port::Image,QImage()));
    AddPort(new Port(2,"绿色通道",Port::Output,Port::Image,QImage()));
    AddPort(new Port(3,"蓝色通道",Port::Output,Port::Image,QImage()));


}

void ChannelSeparation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void ChannelSeparation::execute()
{

    QVariant imgval=GetPortValue(1,Port::Input);
    Image=imgval.value<QImage>();

    uint w=Image.width();
    uint h=Image.height();
    // 创建三个单通道图像
    QImage redChannelImage(w, h, QImage::Format_RGB888);
    QImage greenChannelImage(w, h, QImage::Format_RGB888);
    QImage blueChannelImage(w, h, QImage::Format_RGB888);

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            QColor color = Image.pixelColor(x, y);

            // 获取红、绿和蓝通道的值
            int red = color.red();
            int green = color.green();
            int blue = color.blue();
            // 设置对应通道的像素值
            redChannelImage.setPixelColor(x, y, QColor(red, 0, 0));
            greenChannelImage.setPixelColor(x, y, QColor(0, green, 0));
            blueChannelImage.setPixelColor(x, y, QColor(0, 0, blue));
        }
    }

    SetPortValue(1,redChannelImage,Port::Output);
    SetPortValue(2,greenChannelImage,Port::Output);
    SetPortValue(3,blueChannelImage,Port::Output);

}
