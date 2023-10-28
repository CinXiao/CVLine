#include "datanode.h"



DataNode::DataNode(QPointF pos, QVariant Dat,Port::PortDataType datatype):Node(Node::DataNode,pos)
{


        NodeName="数据";
        setFlag(QGraphicsItem::ItemIsFocusable, true);
        AddPort(new Port(0,"整数",Port::Output,Port::Int));
        textItem = new QGraphicsTextItem(Dat.toString(), this);
        textItem->setPos(2, 25); // 设置文本框位置
        textItem->setTextInteractionFlags(Qt::TextEditorInteraction); // 允许编辑文本
        textItem->setDefaultTextColor(Qt::white);
        TitleColor=Port::PortColorMap[datatype];




}

void DataNode::execute()
{

        int val=textItem->toPlainText().toInt();
        SetPortValue(0,val,Port::Output);
        Node::execute();

}
