#ifndef AND_H
#define AND_H
#include "src/NodeGraphics/node.h"

class And:public Node
{
public:
    And(QPointF pos=QPointF(0,0));
    void execute();
};

#endif // AND_H
