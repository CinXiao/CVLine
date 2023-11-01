#ifndef GETIMAGEINFO_H
#define GETIMAGEINFO_H

#include "src/NodeGraphics/node.h"


class GetImageInfo:public Node
{
public:
    GetImageInfo(QPointF pos=QPointF(0,0));


    void execute();
};

#endif // GETIMAGEINFO_H
