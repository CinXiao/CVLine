#include "print.h"

Print::Print(QPointF pos):Node(Node::FunctionNode,pos)
{
    NodeName="打印输出";
     AddPort(new Port(0,"",Port::InStream,Port::Stream));
     AddPort(new Port(0,"",Port::OutStream,Port::Stream));
    //数据端口
    AddPort(new Port(1,"",Port::Input,Port::String,""));
}

void Print::execute()
{
    QVariant inportDat;
    inportDat=GetPort(1,Port::Input)->Data;
    CVLineDebug::print(inportDat.toString());

}
