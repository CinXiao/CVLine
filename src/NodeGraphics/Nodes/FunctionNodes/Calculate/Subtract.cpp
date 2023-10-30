#include"Subtract.h"

Subtract::Subtract(QPointF pos, Port::PortDataType datatype):Node(Node::FunctionNode, pos)
{
    NodeName="Subtract";
    SetInStreamPort();
    SetOutStreamPort();
    AddPort(new Port(1,"0",Port::Input,datatype));
    AddPort(new Port(2,"0",Port::Input,datatype));
    AddPort(new Port(1,"0",Port::Output,datatype));
}
void Subtract::execute()
{
    QVariant inportDat1,inportDat2;
    inportDat1=GetPort(1,Port::Input)->Data;
    inportDat2=GetPort(2,Port::Input)->Data;
    //设置节点执行完成
    if(inportDat1.type()!=inportDat2.type())
    {
        SetPortValue(0,0,Port::Output);
        return;
    }

    //类型判断设置自己端口的输出值
    if(inportDat1.type()==QVariant::Int)
        SetPortValue(1,inportDat1.toInt()-inportDat2.toInt(),Port::Output);
    if(inportDat1.type()==QVariant::Double)
        SetPortValue(1,inportDat1.toDouble()-inportDat2.toDouble(),Port::Output);


    Node::execute();
}
