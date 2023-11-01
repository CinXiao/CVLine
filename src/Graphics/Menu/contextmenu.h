#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QMenu>

#include "src/NodeGraphics/node.h"
#include "src/NodeGraphics/Nodes/startnode.h"
#include "src/NodeGraphics/Nodes/DataNode/DataNode.h"
#include "src/NodeGraphics/Nodes/FunctionNodes/Calculate/Add.h"
#include "src/NodeGraphics/Nodes/FunctionNodes/Calculate/Subtract.h"
#include "src/NodeGraphics/Nodes/FunctionNodes/ProgramControl/If.h"
#include "src/NodeGraphics/Nodes/FunctionNodes/LogicOperation/Booleanlogic.h"
#include "src/NodeGraphics/Nodes/FunctionNodes/Image/getimageinfo.h"
#include "src/NodeGraphics/Nodes/DataNode/ImageNode.h"
#include "src/NodeGraphics/Nodes/FunctionNodes/ProgramControl/then.h"

class ContextMenu:public QMenu
{
public:
    ContextMenu(QWidget *parent=nullptr);
    Node* GetSelectedNode(QAction *action,QPointF pos);




    QAction *StartAction;


    QMenu *DataMenu;
    QAction *IntAction;
    QAction *DoubleAction;
    QAction *StringAction;
    QAction *BoolAction;
    QAction *BitAction;
    QAction *ImageAction;


    QMenu *FunctionMenu;
    QAction *Add_IntAction;
    QAction *Add_DoubleAction;
    QAction *Add_StringAction;
    QAction *Sub_IntAction;
    QAction *Sub_DoubleAction;

    //布尔逻辑运算
    QMenu *BooleanMenu;
    QAction *AndAction;//与
    QAction *OrAction;//或
    QAction *NoAction;//非
    QAction *NoAndAction;//与非
    QAction *NoOrAction;//或非
    QAction *NotOrAction;//异或
    QAction *SOrAction;//同或
    //图像处理
    QMenu *ImageMenu;
    QAction *GetImageInfoAction;//获取图像信息

    //程序控制
    QMenu *ProgramControlMenu;
    QAction *IfAction;
    QAction *ThenAction;

};

#endif // CONTEXTMENU_H
