#include "datanode.h"



DataNode::DataNode(QPointF pos, QVariant Dat):Node(Node::DataNode,pos)
{


        NodeName="数据输入";
        setFlag(QGraphicsItem::ItemIsFocusable, true);
        AddPort(new Port(0,"整数",Port::Output,Port::Int));
        textItem = new QGraphicsTextItem(Dat.toString(), this);


        QFont font ;
        font.setBold(true);
        font.setPixelSize(15);
        textItem->setFont(font);


        textItem->setPos(2, 42); // 设置文本框位置
        textItem->setTextInteractionFlags(Qt::TextEditorInteraction); // 允许编辑文本
        textItem->setDefaultTextColor(Qt::white);




}

void DataNode::execute()
{
        //看输入是什么类型去转换成什么类型输出

        if(GetPort(0,Port::Output)->portDataType==Port::Int)
        {
                int val=textItem->toPlainText().toInt();
                 SetPortValue(0,val,Port::Output);
        }else if(GetPort(0,Port::Output)->portDataType==Port::Float)
        {
                 float val=textItem->toPlainText().toFloat();
                 SetPortValue(0,val,Port::Output);
        }

        Node::execute();

}
