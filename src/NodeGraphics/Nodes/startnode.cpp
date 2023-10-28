#include "startnode.h"

StartNode::StartNode(QPointF pos):Node(Node::StartNode,pos)
{
    NodeName="开始";
    SetOutStreamPort();

}
