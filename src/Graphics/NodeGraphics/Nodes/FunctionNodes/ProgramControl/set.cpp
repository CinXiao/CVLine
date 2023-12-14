#include "set.h"

#include "src/Graphics/graphicsview.h"


\

Set::Set(QPointF pos):Node(Node::ProgrammeControlNode, pos)
{
    NodeName="Set";

    //添加控制端口
    AddPort(new Port(0,"",Port::InStream,Port::Stream));
    AddPort(new Port(0,"",Port::OutStream,Port::Stream));

    AddPort(new Port(1,"",Port::Input,Port::Int));

    varNameText= new TextInput(QRectF(36,45,50,30), this);
    NodeHeight=150;

}

void Set::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Node::paint(painter,option,widget);

    //绘制提示文字

    //绘制数据类型选择按钮

}

void Set::execute()
{
    QVariant inportDat1;
    inportDat1=GetPort(1,Port::Input)->Data;
    GraphicsView* view=nullptr;
    view=dynamic_cast<GraphicsView*>(scene()->views()[0]);
    if(view!=nullptr)
    {
        view->nodeManager.SetVarValueByName(varNameText->toPlainText(),inportDat1);
    }
}
