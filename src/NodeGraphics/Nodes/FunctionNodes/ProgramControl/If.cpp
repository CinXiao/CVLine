#include "If.h"

If::If(QPointF pos):Node(Node::ProgrammeControlNode, pos)
{
    NodeName="IF";

    //添加控制端口
    AddPort(new Port(0,"",Port::InStream,Port::Stream));
    AddPort(new Port(0,"",Port::OutStream,Port::Stream));
    AddPort(new Port(1,"",Port::OutStream,Port::Stream));


    //数据端口
    AddPort(new Port(1,"",Port::Input,Port::Bool,false));

}

QList<Port *> If::OutputStreamLogicExecution()
{
    QList<Port*>outList;
    // 控制输出端口有多个，默认全部添加，如果需要规定那几个输出端口激活，则需要重载这个函数  IF，Then节点之类的
    //输入值是真把控制输出端口0添加，否则添加端口1
    if(GetPort(1,Port::Input)->Data.toBool())
    {
        outList.append(GetPort(0,Port::OutStream));
    }else
    {
        outList.append(GetPort(1,Port::OutStream));
    }

    return outList;

}
