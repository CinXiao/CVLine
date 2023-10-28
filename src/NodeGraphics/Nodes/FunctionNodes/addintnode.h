#ifndef ADDINTNODE_H
#define ADDINTNODE_H

#include "src/NodeGraphics/node.h"



class AddIntNode:public Node
{
public:
    AddIntNode(QPointF pos=QPointF(0,0));
    void execute();



};

#endif // ADDINTNODE_H
