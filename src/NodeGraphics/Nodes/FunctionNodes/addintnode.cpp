#include "addintnode.h"

AddIntNode::AddIntNode(QPointF pos):Node(Node::FunctionNode, pos)
{
    NodeName="整数相加";
    SetInStreamPort();
    SetOutStreamPort();


    AddPort(new Port(0,"整数A",Port::Input,Port::Int));
    AddPort(new Port(1,"整数B",Port::Input,Port::Int));
    AddPort( new Port(0,"和",Port::Output,Port::Int));


}

void AddIntNode::execute()
{

    //设置节点执行完成
    QVariant a,b;
    a=GetPort(0,Port::Input)->Data;
    b=GetPort(1,Port::Input)->Data;
    int s=a.toInt()+b.toInt();
    //设置自己端口的输出值
    SetPortValue(0,s,Port::Output);

    Node::execute();
}
