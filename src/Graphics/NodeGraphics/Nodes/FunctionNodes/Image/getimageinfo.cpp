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

void GetImageInfo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void GetImageInfo::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    // 创建一个新窗口
    QDialog dialog;
    // 创建一个 QLabel 用于显示图像
    QLabel label(&dialog);
    // 将 QImage 转换为 QPixmap
    QPixmap pixmap = QPixmap::fromImage(Image);
    // 设置 QLabel 显示图像
    label.setPixmap(pixmap);
    // 调整窗口大小以适应图像
    dialog.resize(pixmap.width(), pixmap.height());
    // 显示窗口
    dialog.exec();
}

void GetImageInfo::execute()
{
    QVariant imgval=GetPortValue(1,Port::Input);
    Image=imgval.value<QImage>();
    SetPortValue(1,Image,Port::Output);
    SetPortValue(2,Image.width(),Port::Output);
    SetPortValue(3,Image.height(),Port::Output);

    Node::execute();
}

