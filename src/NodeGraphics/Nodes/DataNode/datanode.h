#ifndef DATANODE_H
#define DATANODE_H
#include<QDebug>
#include<QObject>
#include "src/NodeGraphics/node.h"
class DataNode: public Node
{
public:
    DataNode(QPointF pos=QPointF(0,0), QVariant Dat=0);


    void execute();


private:
    QGraphicsTextItem* textItem;

};

#endif // DATANODE_H
