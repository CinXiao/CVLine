#include "binarization.h"

Binarization::Binarization(QPointF pos):Node(Node::FunctionNode, pos)
{
    NodeName="二值化";
    //添加控制端口
    AddPort(new Port(0,"",Port::InStream,Port::Stream));
    AddPort(new Port(0,"",Port::OutStream,Port::Stream));

    //数据端口
    AddPort(new Port(1,"图像输入",Port::Input,Port::Image,QImage()));
    AddPort(new Port(2,"阈值输入",Port::Input,Port::Int,120));
    AddPort(new Port(1,"二值化图像",Port::Output,Port::Image,QImage()));

    NodeHeight=250;

}

void Binarization::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Node::paint(painter,option,widget);
    // 检查图片是否有效，然后绘制它
    if (!Image.isNull()) {
        // 定义图片位置和大小
        QRectF imageRect(3, 160, 80, 80);
        // 绘制图片
        painter->drawImage(imageRect, Image);
    }
}


void Binarization::execute()
{

    QVariant imgval=GetPortValue(1,Port::Input);
    Image=imgval.value<QImage>();
    QImage ezh=Image.copy();
    int yz=GetPortValue(2,Port::Input).toUInt();
    for (int y = 0; y < ezh.height(); y++) {
        for (int x = 0; x < ezh.width(); x++) {
            QColor color = ezh.pixelColor(x, y);
            // 计算像素的亮度（可以根据需要选择其他颜色通道）
            int brightness = (color.red() + color.green() + color.blue()) / 3;
            if (brightness > yz) {
                // 如果像素亮度高于阈值，设置为白色
                ezh.setPixel(x, y, qRgb(255, 255, 255));
            } else {
                // 如果像素亮度低于或等于阈值，设置为黑色
                ezh.setPixel(x, y, qRgb(0, 0, 0));
            }
        }
    }

    SetPortValue(1,ezh,Port::Output);
    Node::execute();
}
