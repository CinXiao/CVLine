#include "Booleanlogic.h"

Booleanlogic::Booleanlogic(QPointF pos,OperationType optype):Node(Node::FunctionNode, pos),op(optype)
{
    //数据端口
    AddPort(new Port(0,"",Port::Input,Port::Bool,false));
    AddPort(new Port(1,"",Port::Input,Port::Bool,false));
    AddPort(new Port(0,"",Port::Output,Port::Bool,false));

    if (op == AND)
        NodeName = "与";
    else if (op == OR)
        NodeName = "或";
    else if (op == NOAND)
        NodeName = "与非";
    else if (op == NOOR)
        NodeName = "或非";
    else if (op == XOR)
        NodeName = "异或";
    else if (op == SOR)
        NodeName = "同或";
    else if(op==NO)
    {
       NodeName = "非";
      AddPort(new Port(1,"",Port::Output,Port::Bool));
    }



}

void Booleanlogic::execute()
{
    QVariant inportDat1,inportDat2;
    inportDat1=GetPort(0,Port::Input)->Data;
    inportDat2=GetPort(1,Port::Input)->Data;
    bool out;
    if (op == AND)
        out = inportDat1.toBool() && inportDat2.toBool();
    else if (op == OR)
        out = inportDat1.toBool() || inportDat2.toBool();
    if (op == NOAND)
        out = !(inportDat1.toBool() && inportDat2.toBool());
    else if (op == NOOR)
        out = !(inportDat1.toBool() || inportDat2.toBool());
    else if (op == XOR)
        out = (inportDat1.toBool() || inportDat2.toBool()) && !(inportDat1.toBool() && inportDat2.toBool());
    else if (op == SOR)
        out =!(inportDat1.toBool() || inportDat2.toBool()) && !(inportDat1.toBool() && inportDat2.toBool());
     else if (op == NO)
    {
        //非  设置另外一个输出端口的值
              out=!inportDat1.toBool();
        bool  out2 =!inportDat2.toBool();
        SetPortValue(1,out2,Port::Output);
    }
    SetPortValue(0,out,Port::Output);
}
