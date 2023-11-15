#include "division.h"



Division::Division(QPointF pos, Port::PortDataType datatype):Node(Node::FunctionNode, pos)
{


    QVariant val;
    if(datatype==Port::Int)
    {
        NodeName="整数除";
        val=0;
    }
    if(datatype==Port::Double)
    {
        NodeName="小数除";
        val=double(0.0);
    }
    //数据端口
    AddPort(new Port(0,"A",Port::Input,datatype,val));
    AddPort(new Port(1,"B",Port::Input,datatype,val));
    AddPort(new Port(0,"A/B",Port::Output,datatype,val));

}

void Division::execute()
{
    QVariant inportDat1,inportDat2;
    inportDat1=GetPort(0,Port::Input)->Data;
    inportDat2=GetPort(1,Port::Input)->Data;


    //类型判断设置自己端口的输出值
    if(inportDat1.type()==QVariant::Int)
    {

        if(inportDat1.toInt()==0)
        {
            CVLineDebug::print("除数为0，发生在:"+NodeName);
            return;
        }
         SetPortValue(0,inportDat1.toInt()/inportDat2.toInt(),Port::Output);
    }


    if(inportDat1.type()==QVariant::Double)
    {
         if(inportDat1.toDouble()==0)
        {
            CVLineDebug::print("除数为0，发生在:"+NodeName);
            return;
        }
     SetPortValue(0,inportDat1.toDouble()/inportDat2.toDouble(),Port::Output);

    }



}
