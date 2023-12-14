#include "getter.h"

#include "src/Graphics/graphicsview.h"


Getter::Getter(QPointF pos,Port::PortDataType datatype):Node(Node::ProgrammeControlNode, pos)
{

    //添加控制端口
    AddPort(new Port(0,"",Port::InStream,Port::Stream));
    AddPort(new Port(0,"",Port::OutStream,Port::Stream));
    QVariant val;
    if(datatype==Port::Int)
    {
        val=0;
        NodeName="整数Get";
    }
    if(datatype==Port::Double)
    {
        val=double(0.0);
        NodeName="小数Get";
    }
    if(datatype==Port::String)
    {
        val=QString("");
        NodeName="字符串Get";
    }
    if(datatype==Port::Bool)
    {
        val=false;
        NodeName="布尔Get";
    }
    AddPort(new Port(1,"",Port::Output,datatype));

    varNameText= new TextInput(QRectF(36,45,50,30), this);
    NodeHeight=150;

}

void Getter::execute()
{
    GraphicsView* view=nullptr;
    view=dynamic_cast<GraphicsView*>(scene()->views()[0]);
    if(view!=nullptr)
    {
        QVariant var=view->nodeManager.GetVarValueByName(varNameText->toPlainText());

        QVariant outportDat1;
        //数据类型纠正
        Port* port=GetPort(1,Port::Output);
        if(port->portDataType==Port::Int)
        {
            outportDat1=var.toInt();
        }
        if(port->portDataType==Port::Double)
        {
            outportDat1=var.toDouble();
        }
        if(port->portDataType==Port::String)
        {
            outportDat1=var.toString();
        }
        if(port->portDataType==Port::Bool)
        {
            outportDat1=var.toBool();
        }

        SetPortValue(1,outportDat1,Port::Output);
    }


}


void Getter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Node::paint(painter,option,widget);

    //绘制提示文字


    //绘制数据类型选择按钮
}
