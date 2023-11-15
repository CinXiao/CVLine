#include "convertion.h"


Convertion::Convertion(Port::PortDataType port1type, Port::PortDataType port2type, QPointF pos):Node(Node::FunctionNode, pos)
{


    NodeName="转换";
    if(port1type==Port::Int)
        AddPort(new Port(0,"",Port::Input,port1type,0));
    if(port1type==Port::Double)
        AddPort(new Port(0,"",Port::Input,port1type,double(0.0)));
    if(port1type==Port::Bool)
        AddPort(new Port(0,"",Port::Input,port1type,false));
    if(port1type==Port::String)
        AddPort(new Port(0,"",Port::Input,port1type,""));

    if(port2type==Port::Int)
        AddPort(new Port(0,"",Port::Output,port2type,0));
    if(port2type==Port::Double)
        AddPort(new Port(0,"",Port::Output,port2type,double(0.0)));
    if(port2type==Port::Bool)
        AddPort(new Port(0,"",Port::Output,port2type,false));
    if(port2type==Port::String)
        AddPort(new Port(0,"",Port::Output,port2type,""));
}

void Convertion::execute()
{

    QVariant in,out;
    in=GetPortValue(0,Port::Input);
    out=GetPortValue(0,Port::Output);
    if(out.type()==QVariant::Int)
    {
        SetPortValue(0,in.toInt(),Port::Output);
    }else if(out.type()==QVariant::Double)
    {
        SetPortValue(0,double(in.toFloat()),Port::Output);
    }else if(out.type()==QVariant::String)
    {
        SetPortValue(0,in.toString(),Port::Output);
    }else if(out.type()==QVariant::Bool)
    {
        SetPortValue(0,in.toBool(),Port::Output);
    }
    qDebug()<<GetPortValue(0,Port::Output);

}
