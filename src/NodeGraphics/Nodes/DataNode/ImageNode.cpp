#include "ImageNode.h"


ImageNode::ImageNode(QPointF pos):Node(Node::DataNode,pos)
{
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    TitleColor=Port::PortColorMap[Port::Image];
    NodeName=Port::PortDataTypeNameMap[Port::Image];

    Port *port=new Port(0,"",Port::Output,Port::Image,QVariant(Image));
    port->portRect=QRectF( port->portRect.x()+40, port->portRect.y(), port->portRect.width(), port->portRect.height());
    AddPort(port);
    NodeWidth=200;
    NodeHeight=210;


}

void ImageNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    Node::paint(painter,option,widget);

    // 检查图片是否有效，然后绘制它
    if (!Image.isNull()) {
        // 定义图片位置和大小
        QRectF imageRect(3, 45, 150, 150);

        // 绘制图片
        painter->drawImage(imageRect, Image);
    }


}

void ImageNode::execute()
{
    QVariant val(Image);
     SetPortValue(0,val,Port::Output);
}
