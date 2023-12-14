#include "setter.h"

#include "src/Graphics/graphicsview.h"


\

Setter::Setter(QPointF pos,Port::PortDataType datatype):Node(Node::ProgrammeControlNode, pos)
{
    //添加控制端口
    AddPort(new Port(0,"",Port::InStream,Port::Stream));
    AddPort(new Port(0,"",Port::OutStream,Port::Stream));
    QVariant val;
    if(datatype==Port::Int)
    {
        val=0;
        NodeName="整数Set";
    }
    if(datatype==Port::Double)
    {
        val=double(0.0);
        NodeName="小数Set";
    }
    if(datatype==Port::String)
    {
        val=QString("");
        NodeName="字符串Set";
    }
    if(datatype==Port::Bool)
    {
        val=false;
        NodeName="布尔Set";
    }


    AddPort(new Port(1,"",Port::Input,datatype,val));


    varNameText= new TextInput(QRectF(36,45,50,30), this);
    NodeHeight=150;

}

void Setter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Node::paint(painter,option,widget);

    //绘制提示文字

    //绘制数据类型选择按钮

}

void Setter::execute()
{


    GraphicsView* view=nullptr;
    view=dynamic_cast<GraphicsView*>(scene()->views()[0]);

    QVariant inportDat1=GetPortValue(1,Port::Input);


    if(view!=nullptr)
    {
        view->nodeManager.SetVarValueByName(varNameText->toPlainText(),inportDat1);
    }
}
