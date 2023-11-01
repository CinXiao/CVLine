#ifndef THEN_H
#define THEN_H


#include "src/NodeGraphics/node.h"
class Then:public Node
{
public:
    Then(QPointF pos=QPointF(0,0));

    //控制输出端口逻辑重载
    virtual QList<Port*> OutputStreamLogicExecution();
};

#endif // THEN_H
