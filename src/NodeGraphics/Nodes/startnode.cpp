#include "startnode.h"

StartNode::StartNode(QPointF pos):Node(Node::StartNode,pos)
{
    NodeName="开始";
    SetOutStreamPort();

}

void StartNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Node::paint(painter, option, widget);
    // 绘制底色
    QRectF backgroundRect(3,45,150,25);

    painter->drawText(backgroundRect,"从这里开始");
}
