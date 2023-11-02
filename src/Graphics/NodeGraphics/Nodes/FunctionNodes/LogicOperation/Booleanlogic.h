#ifndef AND_H
#define AND_H
#include "src/Graphics/NodeGraphics/node.h"

class Booleanlogic:public Node
{

public:
    enum OperationType{AND,OR,NO,NOAND,NOOR,XOR,SOR};
    Booleanlogic(QPointF pos=QPointF(0,0),OperationType optype=AND);

    OperationType op{AND};
    void execute();
};

#endif // AND_H
