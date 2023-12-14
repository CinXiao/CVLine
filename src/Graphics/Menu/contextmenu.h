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
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/InAndOut/print.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/Image/InAndOut/readimage.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/ProgramControl/Loop/loop.h"

#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/Calculate/mod.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/Calculate/division.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/Calculate/Multiply.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/Calculate/max.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/Calculate/min.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/Compare/equal.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/Compare/less.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/Compare/greater.h"

#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/ProgramControl/get.h"
#include "src/Graphics/NodeGraphics/Nodes/FunctionNodes/ProgramControl/set.h"

#include "src/Graphics/NodeGraphics/Nodes/DataNode/varnode.h"
class ContextMenu:public QMenu
{
public:
    ContextMenu(QWidget *parent=nullptr);
    Node* GetSelectedNode(QAction *action,QPointF pos);

    //输入数据节点
    QMenu *InputDataMenu;
    //变量节点
    QMenu *VarDataMenu;
    //功能节点
    QMenu *FunctionMenu;
        QMenu *IntFunctionMenu;
        QMenu *DoubleFunctionMenu;
        QMenu *StringFunctionMenu;

    //比较运算
    QMenu *CompareMenu;
        QMenu *IntCompareFunctionMenu;
        QMenu *DoubleCompareFunctionMenu;
        QMenu *StringCompareFunctionMenu;
    //布尔逻辑运算
    QMenu *BooleanMenu;
    //图像处理
    QMenu *ImageMenu;
            QMenu *GetImageMenu;
            QMenu *GetImageInfoMenu;
            QMenu *ImageoperateMenu;
            QMenu *ImageFilterMenu;
    //程序控制
    QMenu *ProgramControlMenu;
    //输入输出
    QMenu *IOMenu;
private:
    QMenu* CreateSubMenu(const QString& title);
    QAction* AddMenuItem(QMenu* menu, const QString& title, const std::function<Node*(QPointF)>& nodeCreator);
    //菜单名称和函数map，通过菜单名称可以拿到菜单对应的节点
    std::unordered_map<QAction*, std::function<Node*(QPointF)>> actionToNode;

};

#endif // CONTEXTMENU_H
