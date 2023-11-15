#include "equal.h"


equal::equal(QPointF pos, Port::PortDataType datatype):Node(Node::FunctionNode, pos)
{


    QVariant val;
    if(datatype==Port::Int)
    {
        NodeName="整数等于";
        val=0;
    }
    if(datatype==Port::Double)
    {
          NodeName="小数等于";
        val=double(0.0);
    }

    //添加控制端口
    AddPort(new Port(0,"A",Port::Input,datatype,val));
    AddPort(new Port(1,"B",Port::Input,datatype,val));
    AddPort(new Port(0,"=",Port::Output,Port::Bool,false));
}
void equal::execute()
{

    QVariant inportDat1,inportDat2;
    inportDat1=GetPort(0,Port::Input)->Data;
    inportDat2=GetPort(1,Port::Input)->Data;


    //类型判断设置自己端口的输出值
    if(inportDat1.type()==QVariant::Int)
    {
        SetPortValue(0,inportDat1.toInt()==inportDat2.toInt(),Port::Output);
    }
    if(inportDat1.type()==QVariant::Double)
    {
        SetPortValue(0,inportDat1.toDouble()==inportDat2.toDouble(),Port::Output);
    }

}
