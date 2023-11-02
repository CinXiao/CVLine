#include "startnode.h"

StartNode::StartNode(QPointF pos):Node(Node::StartNode,pos)
{
    NodeName="开始";
    //添加输出控制端口
    AddPort(new Port(0,"",Port::OutStream,Port::Stream));

}

void StartNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Node::paint(painter, option, widget);
    // 绘制底色
    QRectF backgroundRect(3,45,150,25);

    painter->drawText(backgroundRect,"从这里开始");
}
