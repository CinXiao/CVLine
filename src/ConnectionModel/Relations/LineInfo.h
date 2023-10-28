#ifndef LINEINFO_H
#define LINEINFO_H
#include "PortInfo.h"


class LineInfo
{
public:
    PortInfo  PortInfo1;//端口信息1
    PortInfo  PortInfo2;//端口信息2
    BezierCurveItem *line{nullptr};//线

    PortInfo GetOtherPortNodeInfoByPort(Port*port)
    {
        return PortInfo1.port!=port?PortInfo1: PortInfo2;
    }
};
#endif // LINEINFO_H
