#ifndef LINEINFO_H
#define LINEINFO_H
#include "PortInfo.h"


class LineInfo
{
public:
    PortInfo  PortInfo1;//端口信息1
    PortInfo  PortInfo2;//端口信息2
    BezierCurveItem *line{nullptr};//线
    LineInfo(){}
    LineInfo(PortInfo info1,PortInfo info2,BezierCurveItem *line):
        PortInfo1(info1),PortInfo2(info2),line(line)
    {

    }
    PortInfo GetOtherPortNodeInfoByPort(Port*port)
    {
        return PortInfo1.port!=port?PortInfo1: PortInfo2;
    }
    PortInfo GetPortNodeInfoByPort(Port*port)
    {
        return PortInfo1.port==port?PortInfo1: PortInfo2;
    }
};
#endif // LINEINFO_H
