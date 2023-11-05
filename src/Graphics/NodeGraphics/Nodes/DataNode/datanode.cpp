#include "datanode.h"




DataNode::DataNode(QPointF pos, QVariant Dat, Port::PortDataType datatype):Node(Node::DataNode,pos)
{

        TitleColor=Port::PortColorMap[datatype];
        NodeName=Port::PortDataTypeNameMap[datatype];
        setFlag(QGraphicsItem::ItemIsFocusable, true);
        if(datatype==Port::Int)
        {
            AddPort(new Port(0,"",Port::Output,datatype,int(0)));
        }else if(datatype==Port::Double)
        {
            AddPort(new Port(0,"",Port::Output,datatype,double(0.0)));
        }else if(datatype==Port::Bool)
        {
            AddPort(new Port(0,"",Port::Output,datatype,false));
        }else if(datatype==Port::Bit)
        {
            AddPort(new Port(0,"",Port::Output,datatype,0));
        }else if(datatype==Port::String)
        {
            AddPort(new Port(0,"",Port::Output,datatype,QString("")));
        }
        textItem = new TextInput(QRectF(3,45,50,30),Dat, this);

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
                 SetPortValue(0,val.toString(),Port::Output);
        }else if(GetPort(0,Port::Output)->portDataType==Port::Bool)
        {
                 QVariant val(textItem->toPlainText());
                 qDebug()<<val.toBool();
                 SetPortValue(0,val.toBool(),Port::Output);
        }

}
