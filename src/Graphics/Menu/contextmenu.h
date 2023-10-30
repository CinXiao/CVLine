#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QMenu>

#include "src/NodeGraphics/node.h"
#include "src/NodeGraphics/Nodes/startnode.h"
#include "src/NodeGraphics/Nodes/DataNode/DataNode.h"
#include "src/NodeGraphics/Nodes/FunctionNodes/Calculate/Add.h"
#include "src/NodeGraphics/Nodes/FunctionNodes/Calculate/Subtract.h"
#include "src/NodeGraphics/Nodes/FunctionNodes/ProgramControl/If.h"
#include "src/NodeGraphics/Nodes/FunctionNodes/LogicOperation/And.h"
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

    QMenu *FunctionMenu;
    QAction *Add_IntAction;
    QAction *Add_DoubleAction;
    QAction *Add_StringAction;
    QAction *Sub_IntAction;
    QAction *Sub_DoubleAction;

    QAction *AndAction;//与
    QAction *OrAction;//或
    QAction *NoAction;//非

    QMenu *ProgramControlMenu;
    QAction *IfAction;


};

#endif // CONTEXTMENU_H
