#include "projectfile.h"


void ProjectFile::SaveProjct(GraphicsView *view,QUrl url)
{




    QJsonObject Json{
    };


    QJsonArray NodeArr;
    //记录节点
    for(auto node:view->nodeManager.NodeList)
    {
        QJsonObject nodejson;
        //节点名
        nodejson["Name"]=node->NodeName;
        //节点ID
        nodejson["ID"]=int(node->NodeID);
        //坐标
        nodejson["X"]=node->pos().x();
        nodejson["Y"]=node->pos().y();
        //节点类型
        nodejson["NodeType"]=node->nodeType;

        //记录端口
        QJsonArray nodeportarr;
        for(auto port:node->portList)
        {
            QJsonObject portjson;
            portjson["Type"]=port->portType;
            portjson["PortID"]=int(port->ID);
            portjson["DataType"]=port->portDataType;
            portjson["Data"]=port->Data.toString();
            nodeportarr.append(portjson);
        }

        nodejson["Port"]=nodeportarr;
        NodeArr.append(nodejson);
    }
    Json["Nodes"]=NodeArr;

    //记录连接
    QJsonArray ConnectionArr;
    for(auto relation:view->nodeManager.PortLineInfoList)
    {
        QJsonObject connectionjson;
       //节点1ID
        connectionjson["OriginNode"]=int(relation.PortInfo1.node->NodeID);
       // 节点1端口ID
        connectionjson["OriginPort"]=int(relation.PortInfo1.port->ID);
        //节点1端口类型
       connectionjson["OriginPortType"]=int(relation.PortInfo1.port->portType);

       //节点2ID
        connectionjson["TargetNode"]=int(relation.PortInfo2.node->NodeID);
       // 节点2端口ID
        connectionjson["TargetPort"]=int(relation.PortInfo2.port->ID);
        //节点2端口类型
       connectionjson["TargetPortType"]=int(relation.PortInfo2.port->portType);

        ConnectionArr.append(connectionjson);
    }

    Json["Connections"]=ConnectionArr;

    QJsonDocument doc(Json);
    QFile file("C:/Users/Sun/Desktop/dat.json");

    file.open(QIODevice::WriteOnly);
    file.write(doc.toJson());

    file.close();
}

GraphicsView *ProjectFile:: OpenProject(QUrl fileurl)
{
    GraphicsView *view=new GraphicsView();


    QFile file(fileurl.toLocalFile());
    file.open(QIODevice::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    QJsonObject rootObject = doc.object();
    QJsonArray nodesArray = rootObject.value("Nodes").toArray();

    //解析节点
    foreach (const QJsonValue &nodeValue, nodesArray)
    {
        QJsonObject nodeObject = nodeValue.toObject();

        QPointF pos(nodeObject["X"].toInt(),nodeObject["Y"].toInt());

        auto it = NodeMap.find(nodeObject["Name"].toString());

        if (it != NodeMap.end()) {


            Node*node;
            //菜单和函数表中pair的第二个元素是匿名函数，需要一个传入的坐标pos
            std::function<Node*(QPointF)> func=*it;
            node=func(pos);
            node->NodeID=nodeObject["ID"].toInt();
            //设置端口值

            view->nodeManager.AddNode(node);

        }

    }

    //解析连接信息
     QJsonArray connectionArray = rootObject.value("Connections").toArray();
    foreach (const QJsonValue &connetValue, connectionArray)
     {
         QJsonObject connectionObject = connetValue.toObject();
         int OriginNode=connectionObject["OriginNode"].toInt();
         int OriginPort=connectionObject["OriginPort"].toInt();
         int OriginPortType=connectionObject["OriginPortType"].toInt();
         int TargetNode=connectionObject["TargetNode"].toInt();
         int TargetPort=connectionObject["TargetPort"].toInt();
         int TargetPortType=connectionObject["TargetPortType"].toInt();

         //连接
          view->nodeManager.PortConnectByID(OriginNode,OriginPort,OriginPortType,TargetNode,TargetPort,TargetPortType);

     }


      view->nodeManager.UpDateAlldNode();
    return view;
}
