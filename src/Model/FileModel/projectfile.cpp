#include "projectfile.h"


void ProjectFile::SaveProjct(GraphicsView *view,QUrl url)
{




    QJsonObject Json{
    };


    QJsonArray NodeArr;
    for(auto node:view->nodeManager.NodeList)
    {
        QJsonObject nodejson;
        //节点名
        nodejson["Name"]=node->NodeName;
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
            portjson["DataType"]=port->portDataType;
            portjson["Data"]=port->Data.toString();

            nodeportarr.append(portjson);
        }

        nodejson["Port"]=nodeportarr;
        NodeArr.append(nodejson);
    }

    Json["Nodes"]=NodeArr;

    QJsonDocument doc(Json);
    QFile file("C:/Users/Sun/Desktop/dat.json");

    file.open(QIODevice::WriteOnly);
    file.write(doc.toJson());

    file.close();
}
