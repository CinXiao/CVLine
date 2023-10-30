#include "And.h"

And::And(QPointF pos):Node(Node::FunctionNode, pos)
{
    NodeName="&";
    //数据端口
    AddPort(new Port(0,"",Port::Input,Port::Bool));
    AddPort(new Port(1,"",Port::Input,Port::Bool));
    AddPort(new Port(0,"",Port::Output,Port::Bool));
}

void And::execute()
{
    QVariant inportDat1,inportDat2;
    inportDat1=GetPort(0,Port::Input)->Data;
    inportDat2=GetPort(1,Port::Input)->Data;
    bool out=inportDat1.toBool()&inportDat2.toBool();
    SetPortValue(0,out,Port::Output);
}
