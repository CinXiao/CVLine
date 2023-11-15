#ifndef LOOP_H
#define LOOP_H


#include "src/Entity/Relations/PortInfo.h"
#include "src/Entity/Relations/LineInfo.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/ProgramControl/Loop/circulateinterface.h"
class Loop : public CirculateInterface
{
public:
    Loop(QPointF pos=QPointF(0,0));

    //控制输出端口逻辑重载
    virtual QList<Port*> OutputStreamLogicExecution();
    virtual void executeCirculate();


};

#endif // LOOP_H
