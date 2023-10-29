#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QMenu>

#include "src/NodeGraphics/node.h"
#include "src/NodeGraphics/Nodes/startnode.h"
#include "src/NodeGraphics/Nodes/DataNode/DataNode.h"
#include "src/NodeGraphics/Nodes/FunctionNodes/Add.h"
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


    QMenu *FunctionMenu;
    QAction *Add_IntAction;
    QAction *Add_DoubleAction;
    QAction *Add_StringAction;


};

#endif // CONTEXTMENU_H
