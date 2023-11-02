#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QMenu>
#include "src/Graphics/NodeGraphics/node.h"
#include "src/Graphics/NodeGraphics/Port/Port.h"
#include "src/Graphics/NodeGraphics/Nodes/startnode.h"
#include "src/Graphics/NodeGraphics/Nodes/DataNode/DataNode.h"
#include "src/Graphics/NodeGraphics/Nodes/DataNode/ImageNode.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/Calculate/Add.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/Calculate/Subtract.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/Image/binarization.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/ProgramControl/If.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/Image/getimageinfo.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/LogicOperation/Booleanlogic.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/Image/imageconversion.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/Image/channelseparation.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/Image/imageadjustment.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/ProgramControl/then.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/Image/channelmerging.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/Image/gaussianblur.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/Image/InAndOut/readimage.h"

class ContextMenu:public QMenu
{
public:
    ContextMenu(QWidget *parent=nullptr);
    Node* GetSelectedNode(QAction *action,QPointF pos);

   //数据节点
    QMenu *DataMenu;
    //功能节点
    QMenu *FunctionMenu;

    //布尔逻辑运算
    QMenu *BooleanMenu;
    //图像处理
    QMenu *ImageMenu;

    //程序控制
    QMenu *ProgramControlMenu;
private:
    QMenu* CreateSubMenu(const QString& title);
    QAction* AddMenuItem(QMenu* menu, const QString& title, const std::function<Node*(QPointF)>& nodeCreator);
    //菜单名称和函数map，通过菜单名称可以拿到菜单对应的节点
    std::unordered_map<QAction*, std::function<Node*(QPointF)>> actionToNode;

};

#endif // CONTEXTMENU_H
