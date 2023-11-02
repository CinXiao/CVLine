#ifndef IF_H
#define IF_H


#include "src/Graphics/NodeGraphics/node.h"

class If:public Node
{
public:
    If(QPointF pos=QPointF(0,0));

    //控制输出端口逻辑重载
    virtual QList<Port*> OutputStreamLogicExecution();
};

#endif // IF_H
