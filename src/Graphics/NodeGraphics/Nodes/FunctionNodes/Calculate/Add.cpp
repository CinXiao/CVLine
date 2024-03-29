#include "Add.h"

AddNode::AddNode(QPointF pos,Port::PortDataType datatype):Node(Node::FunctionNode, pos)
{

    QVariant val;
    if(datatype==Port::Int)
    {
      val=0;
    NodeName="整数加";
    }
    if(datatype==Port::Double)

    {
         val=double(0.0);
        NodeName="小数加";
    }
    if(datatype==Port::String)

    {
        val=QString("");
        NodeName="字符串加";
    }

    //数据端口
    AddPort(new Port(0,"A",Port::Input,datatype,val));
    AddPort(new Port(1,"B",Port::Input,datatype,val));
    AddPort(new Port(0,"A+B",Port::Output,datatype,val));

}
void AddNode::execute()
{

    QVariant inportDat1,inportDat2;
    inportDat1=GetPort(0,Port::Input)->Data;
    inportDat2=GetPort(1,Port::Input)->Data;


     //类型判断设置自己端口的输出值
    if(inportDat1.type()==QVariant::Int)
        SetPortValue(0,inportDat1.toInt()+inportDat2.toInt(),Port::Output);
    if(inportDat1.type()==QVariant::Double)
        SetPortValue(0,inportDat1.toDouble()+inportDat2.toDouble(),Port::Output);
}
