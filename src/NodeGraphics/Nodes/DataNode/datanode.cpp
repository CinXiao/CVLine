#include "datanode.h"



void DataNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

     Node::paint(painter, option, widget);
    // 绘制底色//绘制文本输入框背景
     painter->setPen(Qt::NoPen);
    QRectF backgroundRect(textItem->x(),textItem->y(),50,25);
    painter->setBrush(QBrush(QColor(30, 30, 30,100))); // 设置底色
    painter->drawRoundedRect(backgroundRect,5,5);

}

DataNode::DataNode(QPointF pos, QVariant Dat, Port::PortDataType datatype):Node(Node::DataNode,pos)
{

        TitleColor=Port::PortColorMap[datatype];
        NodeName=Port::PortDataTypeNameMap[datatype];
        setFlag(QGraphicsItem::ItemIsFocusable, true);
        if(datatype==Port::Int)
        {
            AddPort(new Port(0,Dat.toString(),Port::Output,datatype,0));
        }else if(datatype==Port::Double)
        {
            AddPort(new Port(0,Dat.toString(),Port::Output,datatype,0.0));
        }else if(datatype==Port::Bool)
        {
            AddPort(new Port(0,Dat.toString(),Port::Output,datatype,false));
        }
        textItem = new TextInput(Dat, this);
}


void DataNode::execute()
{
        //看输入是什么类型去转换成什么类型输出

        if(GetPort(0,Port::Output)->portDataType==Port::Int)
        {
                QVariant val=textItem->toPlainText().toInt();
                 SetPortValue(0,val,Port::Output);
        }else if(GetPort(0,Port::Output)->portDataType==Port::Double)
        {
                 QVariant val(textItem->toPlainText().toDouble());
                 SetPortValue(0,val,Port::Output);
        }else if(GetPort(0,Port::Output)->portDataType==Port::String)
        {
                 QVariant val(textItem->toPlainText());
                 SetPortValue(0,val,Port::Output);
        }else if(GetPort(0,Port::Output)->portDataType==Port::Bool)
        {
                 QVariant val(textItem->toPlainText());
                 qDebug()<<val.toBool();
                 SetPortValue(0,val.toBool(),Port::Output);
        }

        Node::execute();

}
