#include "then.h"

Then::Then(QPointF pos):Node(Node::ProgrammeControlNode, pos)
{
    NodeName="Then";

    //输入控制端口
    AddPort(new Port(0,"",Port::InStream,Port::Stream));
    //输出控制端口
    AddPort(new Port(0,"Execute first",Port::OutStream,Port::Stream));
    AddPort(new Port(1,"Execute Second",Port::OutStream,Port::Stream));
    AddPort(new Port(2,"Execute Third",Port::OutStream,Port::Stream));
    AddPort(new Port(3,"Execute Fourth",Port::OutStream,Port::Stream));
    AddPort(new Port(4,"Execute Fifth",Port::OutStream,Port::Stream));
    AddPort(new Port(5,"Execute Sixth",Port::OutStream,Port::Stream));
    AddPort(new Port(6,"Execute Seventh",Port::OutStream,Port::Stream));
    AddPort(new Port(7,"Execute Eighth",Port::OutStream,Port::Stream));
    AddPort(new Port(8,"Execute Ninth",Port::OutStream,Port::Stream));
    AddPort(new Port(9,"Execute Tenth",Port::OutStream,Port::Stream));
}

QList<Port *> Then::OutputStreamLogicExecution()
{

    QList<Port*>outList;

    //把输出端口按顺端口ID顺序添加
    outList.append(GetPort(0,Port::OutStream));
    outList.append(GetPort(1,Port::OutStream));
    outList.append(GetPort(2,Port::OutStream));
    outList.append(GetPort(3,Port::OutStream));
    outList.append(GetPort(4,Port::OutStream));
    outList.append(GetPort(5,Port::OutStream));
    outList.append(GetPort(6,Port::OutStream));
    outList.append(GetPort(7,Port::OutStream));
    outList.append(GetPort(8,Port::OutStream));
    outList.append(GetPort(9,Port::OutStream));
    return outList;
}
