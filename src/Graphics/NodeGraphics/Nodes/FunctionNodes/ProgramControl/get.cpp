#include "get.h"

#include "src/Graphics/graphicsview.h"


Get::Get(QPointF pos):Node(Node::ProgrammeControlNode, pos)
{
    NodeName="Get";

    //添加控制端口
    AddPort(new Port(0,"",Port::InStream,Port::Stream));
    AddPort(new Port(0,"",Port::OutStream,Port::Stream));

    AddPort(new Port(1,"",Port::Output,Port::Int));

    varNameText= new TextInput(QRectF(36,45,50,30), this);
    NodeHeight=150;

}

void Get::execute()
{
    QVariant outportDat1;
    outportDat1=GetPort(1,Port::Output)->Data;

    GraphicsView* view=nullptr;
    view=dynamic_cast<GraphicsView*>(scene()->views()[0]);
    if(view!=nullptr)
    {
        QVariant dat=view->nodeManager.GetVarValueByName(varNameText->toPlainText());
        SetPortValue(1,dat,Port::Output);
    }


}


void Get::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Node::paint(painter,option,widget);

    //绘制提示文字




    //绘制数据类型选择按钮


}
