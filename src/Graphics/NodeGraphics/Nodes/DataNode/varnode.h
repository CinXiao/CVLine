#ifndef VARNODE_H
#define VARNODE_H



#include "src/Graphics/NodeGraphics/node.h"
#include "src/Graphics/NodeGraphics/Nodes/DataNode/TextInput/textinput.h"
class VarNode: public Node
{
public:
    VarNode(QPointF pos=QPointF(0,0), QVariant Dat=0,Port::PortDataType datatype=Port::Int);

   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    TextInput* varNameText;

  //变量值
   QVariant Var;

   bool Valid=false;
};

#endif // VARNODE_H
