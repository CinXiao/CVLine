#ifndef NODE_H
#define NODE_H


#include<QList>
#include <QRect>
#include<QObject>
#include <QPointF>
#include <QVariant>
#include <QPainter>
#include <QGraphicsItem>
#include<QGraphicsScene>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include<opencv2/opencv.hpp>
#include "src/Graphics/NodeGraphics/Port/Port.h"
#include "src/Graphics/LineGraphics/beziercurveitem.h"
#include "src/Entity/Relations/StreamPortinfo.h"
#include "src/Model/DebugModel/cvlinedebug.h"
typedef BezierCurveItem Line;

class Node: public QGraphicsItem
{

public:

    //节点类型
    enum NodeType { BaseNode,
                    StartNode,
                    FunctionNode,
                    ProgrammeControlNode,
                    DataNode};

    Node(NodeType nodetype=Node::BaseNode, QPointF pos=QPointF(0,0));

    QRectF boundingRect() const ;


    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event)override;


    //添加端口
    void AddPort(Port *port);


    //设置端口值
    void SetPortValue(uint portID,QVariant data,Port::PortType type);
    //获取端口值
    QVariant GetPortValue(uint portID,Port::PortType type);
    //获取端口
    Port *GetPort(uint portID,Port::PortType type);




    //设置端口数据类型
    void SetPortDataType(uint portId,Port::PortType porttype,Port::PortDataType datatype);

    //拿到控制端口信息
    StreamPortinfo GetStreamInfo();

    //控制输出端口有多个，默认全部添加，如果需要规定那几个输出端口激活，则需要重载这个函数  IF，Then节点之类的
    virtual QList<Port*> OutputStreamLogicExecution();


    //检测点是否在端口上
    bool CheckPortByPos(QPointF pos);
   //获取点上的端口
    Port*GetPortByPos(QPointF pos);


    //获取输入端口数量
    uint GetInputCount()const ;
     //获取输出端口数量
    uint GetOutCount()const ;


    QList<Port*> GetInport();//获取输入端口
    QList<Port*> GetOutport();//获取输入端口
    QList<Port*> GetConnectedInport();//获取已经连接的输入端口
    QList<Port*> GetConnectedOutport();//获取已经连接的输出端口

    QString NodeName{"Node"};   //节点名字

    NodeType nodeType{BaseNode};//节点类型

    QColor TitleColor;//标题颜色
    uint NodeHeight=80;
    uint NodeWidth=160;

    bool IsExecuted=false;


    virtual void execute();//节点执行逻辑
    void NodeRun();//节点运行

private:
    QList<Port*> portList;//端口列表

    //节点类型标题颜色表  各种颜色都是经过哥哥我精心挑选的
    inline static QMap<NodeType,QColor> TitleColorMap
        {
            {BaseNode,QColor(100,100,100)},
            {StartNode,QColor(200,0,0)},
            {ProgrammeControlNode,QColor(200,100,0)},
            {FunctionNode,QColor(20,80,150)},
            {DataNode,QColor(220, 200, 20)},

        };

};

#endif // NODE_H
