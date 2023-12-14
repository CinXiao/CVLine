#ifndef NODEMANAGER_H
#define NODEMANAGER_H
#include "src/Entity/Relations/PortInfo.h"
#include "src/Entity/Relations/LineInfo.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/Conversion/convertion.h"

#include "src/Graphics/NodeGraphics/Nodes/DataNode/varnode.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/ProgramControl/Loop/circulateinterface.h"
#include<unordered_set>
#include <QGraphicsView>

class NodeManager
{

public:
    NodeManager( QGraphicsView *view);

    //通过点拿到端口信息     即这个点是不是在端口上
    PortInfo GetPortByPos( QPoint pos);
    //通过点拿到节点     即这个点是不是在节点上
    Node* GetNodeByPos(QPoint pos);

    //通过端口拿到与该端口连接的所有端口信息信息
    QList<PortInfo> GetNodeAndPortListByPort(Port* port);

    //通过端口拿到与该端口连接的所有线信息
    QList<LineInfo> GetLineInfoListByPort(Port* port);

    //获取连接到节点上输入端口上的所有端口信息
    QList<PortInfo> GetConnectedInPortInfo(Port* port);

    //通过端口拿到与该端口连接的节点和端口信息列表  (只会拿到一个，比如输入口只能有一个输入节点)
    PortInfo GetNodeAndPortByPort(Port* port);

    //通过节点ID，端口ID，端口类型拿到端口信息
    PortInfo GetPortInfoById(int nodeId,int portid,int porttype);

    //拿到节点程序控制输出端口节点信息表  控制输出端口连接的所有的节点
    virtual QList<PortInfo> GetOutStreamPortInfoByNode(Node*node);

    //拿到与该节点控制输入端口节点信息  因为输入只能有一个，所以只会存在一个节点与输入端口连接
    PortInfo GetInStreamPortInfoByNode(Node*node);

    //端口类型检测
    bool PortTypeCheck(PortInfo info1,PortInfo info2);
    //端口连接单调性检测
    bool PortMonotonicityCheck(PortInfo info1,PortInfo info2);
    //端口数据类型检测
    bool PortDataTypeCheck(PortInfo info1,PortInfo info2);

    //通过遍历所有变量节点来判断某个变量名是否已经被声明了
    bool VarNameIsDefine(Node*n, QString varName);

    //通过变量名设置变量值
    void SetVarValueByName(QString varName,QVariant dat);
    //通过变量名获取变量值
    QVariant GetVarValueByName(QString varName);

    //检测回环
    //从一个端口出发看看能不能到达这个端口，如果可以到达那么就是回环，如果最后是空的端口那么就不是回环
    bool CycleCheck();

    //通过点更新节点线的位置
    void UpdateNode(QPoint pos);
    //更新节点线的位置
    void UpDateNode(Node*node);
    //更新选中的节点线的位置
    void UpDateSelectedNode();

    //更新所有节点
    void UpDateAlldNode();

    //添加一条连线关系
    void AddRelation(LineInfo info);

    //执行
    void Run();

    //节点执行 递归
    void NodeRun(QList<PortInfo> portnodeinfolist);
    //节点执行完成以后刷新
    void NodeReflush();


    //添加节点
    void AddNode(Node*node);

    //通过ID连接连个端点
    void PortConnectByID(int orginNodeID,int orginPortID,int orginPortType,int targetNodeID,int targetPortID,int targetPortType);
    //连接两个端点
    void PortConnect(PortInfo port1, PortInfo port2);
    //重新连接两个端点
    void RePortConnect(PortInfo port1, PortInfo port2);
    //尝试连接两个类型不同的端点
    void PortConvertConnect(PortInfo port1, PortInfo port2);
    //检查数据是否可以转换
    bool PortIsConvertion(PortInfo port1, PortInfo port2);

    //删除一个端点之间所有连接的线
    void DeletePortConnect(PortInfo portinfo1);


    //删除选中的节点和线
    void DeleteSelected();


public:
    //端口连线信息列表
    QList<LineInfo> PortLineInfoList;

    //节点表
     QList<Node*>NodeList;

    //场景
    QGraphicsView *view;


};

#endif // NODEMANAGER_H
