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
        connectionjson["OriginNode"]=QString::number(relation.PortInfo1.node->NodeID);
       // 节点1端口ID
        connectionjson["OriginPort"]=QString::number(relation.PortInfo1.port->ID);
        //节点1端口类型
       connectionjson["OriginPortType"]=QString::number(relation.PortInfo1.port->portType);

       //节点2ID
        connectionjson["TargetNode"]=QString::number(relation.PortInfo2.node->NodeID);
       // 节点2端口ID
        connectionjson["TargetPort"]=QString::number(relation.PortInfo2.port->ID);
        //节点2端口类型
       connectionjson["TargetPortType"]=QString::number(relation.PortInfo2.port->portType);

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
            view->nodeManager.AddNode(node);

        }

    }
    return view;
}
