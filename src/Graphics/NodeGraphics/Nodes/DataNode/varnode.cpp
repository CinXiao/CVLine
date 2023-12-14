#include "varnode.h"

#include "src/Graphics/graphicsview.h"



VarNode::VarNode(QPointF pos, QVariant Dat, Port::PortDataType datatype):Node(Node::VarNode,pos),Var(Dat)
{

    TitleColor=Port::PortColorMap[datatype];
    NodeName=Port::PortDataTypeNameMap[datatype]+"变量";

    varNameText= new TextInput(QRectF(55,45,50,30), this);
    NodeHeight=120;


}

void VarNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Node::paint(painter,option,widget);


    QFont titleFont = painter->font();
    titleFont.setBold(true);
    titleFont.setPixelSize(15);
    painter->setFont(titleFont);
    painter->setPen(Qt::white); // 设置标题文本颜色

    // 添加标题
    painter->drawText(QRectF(5,45,45,30), Qt::AlignCenter, "变量名");
    painter->drawText(QRectF(5,80,45,30), Qt::AlignCenter, "值");


    GraphicsView* view=nullptr;
    view=dynamic_cast<GraphicsView*>(scene()->views()[0]);


    if(view!=nullptr)
    {
        Valid=view->nodeManager.VarNameIsDefine(this,varNameText->toPlainText());
        //绘制变量值
        if(varNameText->toPlainText().isEmpty())
        {

            painter->setPen(Qt::red); // 设置标题文本颜色
            painter->drawText(QRectF(50,85,100,30), Qt::AlignLeft, "未设置变量名");
        }
        else if(Valid)
        {
            painter->setPen(Qt::white); // 设置标题文本颜色
            painter->drawText(QRectF(50,85,100,30), Qt::AlignLeft,Var.toString());
        }else
        {
            painter->setPen(Qt::red); // 设置标题文本颜色
            painter->drawText(QRectF(50,85,100,30), Qt::AlignLeft, "变量名冲突");
        }

    }






}
