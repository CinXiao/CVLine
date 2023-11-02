#include "contextmenu.h"




ContextMenu::ContextMenu(QWidget *parent):QMenu(parent)
{
    ProgramControlMenu = CreateSubMenu("控制");
    DataMenu = CreateSubMenu("数据");
    FunctionMenu = CreateSubMenu("计算");
    BooleanMenu = CreateSubMenu("布尔逻辑");
    ImageMenu = CreateSubMenu("图像处理");

    AddMenuItem(ImageMenu, "图像", [](QPointF pos) { return new ImageNode(pos); });
    AddMenuItem(ImageMenu, "依次输出目录图像", [](QPointF pos) { return new ReadImage(pos); });
    AddMenuItem(ImageMenu, "获取图像信息", [](QPointF pos) { return new GetImageInfo(pos); });
    AddMenuItem(ImageMenu, "图像调整", [](QPointF pos) { return new ImageAdjustment(pos); });
    AddMenuItem(ImageMenu, "二值化", [](QPointF pos) { return new Binarization(pos); });
    AddMenuItem(ImageMenu, "通道分离", [](QPointF pos) { return new ChannelSeparation(pos); });
    AddMenuItem(ImageMenu, "通道合并", [](QPointF pos) { return new ChannelMerging(pos); });
    AddMenuItem(ImageMenu, "图像转换", [](QPointF pos) { return new ImageConversion(pos); });
    AddMenuItem(ImageMenu, "高斯模糊", [](QPointF pos) { return new GaussianBlur(pos); });


    AddMenuItem(ProgramControlMenu, "开始", [](QPointF pos) { return new StartNode(pos); });
    AddMenuItem(ProgramControlMenu, "IF", [](QPointF pos) { return new If(pos); });
    AddMenuItem(ProgramControlMenu, "Then", [](QPointF pos) { return new Then(pos); });

    AddMenuItem(DataMenu, "整数", [](QPointF pos) { return new DataNode(pos, 0, Port::Int); });
    AddMenuItem(DataMenu, "小数", [](QPointF pos) { return new DataNode(pos, 0.0, Port::Double); });
    AddMenuItem(DataMenu, "布尔", [](QPointF pos) { return new DataNode(pos, false, Port::Bool); });
    AddMenuItem(DataMenu, "比特", [](QPointF pos) { return new DataNode(pos, 0, Port::Bit); });
    AddMenuItem(DataMenu, "字符串", [](QPointF pos) { return new DataNode(pos, "", Port::String); });

    AddMenuItem(FunctionMenu, "整数相加", [](QPointF pos) { return new AddNode(pos,Port::Int); });
    AddMenuItem(FunctionMenu, "小数相加", [](QPointF pos) { return new AddNode(pos, Port::Double); });
    AddMenuItem(FunctionMenu, "字符串相加", [](QPointF pos) { return new AddNode(pos, Port::String); });
    AddMenuItem(FunctionMenu, "整数相减", [](QPointF pos) { return new Subtract(pos, Port::Int); });
    AddMenuItem(FunctionMenu, "小数相减", [](QPointF pos) { return new Subtract(pos, Port::Double); });
    AddMenuItem(BooleanMenu, "与", [](QPointF pos) { return new Booleanlogic(pos, Booleanlogic::AND); });
    AddMenuItem(BooleanMenu, "或", [](QPointF pos) { return new Booleanlogic(pos, Booleanlogic::OR); });
    AddMenuItem(BooleanMenu, "非", [](QPointF pos) { return new Booleanlogic(pos, Booleanlogic::NO); });
    AddMenuItem(BooleanMenu, "异或", [](QPointF pos) { return new Booleanlogic(pos, Booleanlogic::XOR); });
    AddMenuItem(BooleanMenu, "同或", [](QPointF pos) { return new Booleanlogic(pos, Booleanlogic::SOR); });
    AddMenuItem(BooleanMenu, "与非", [](QPointF pos) { return new Booleanlogic(pos, Booleanlogic::NOAND); });
    AddMenuItem(BooleanMenu, "或非", [](QPointF pos) { return new Booleanlogic(pos, Booleanlogic::NOOR); });

}

Node *ContextMenu::GetSelectedNode(QAction *action,QPointF pos)
{
    //获取选中的菜单对应的节点
   auto it = actionToNode.find(action);
   if (it != actionToNode.end()) {
       //菜单和函数表中pair的第二个元素是匿名函数，需要一个传入的坐标pos
       return (it->second)(pos);
   }
   return nullptr;
}

QMenu *ContextMenu::CreateSubMenu(const QString &title)
{
   //创建
    QMenu* submenu = new QMenu(title);
    addMenu(submenu);
    return submenu;
}

QAction *ContextMenu::AddMenuItem(QMenu *menu, const QString &title, const std::function<Node *(QPointF)> &nodeCreator)
{
    //给一个菜单添加子菜单
    QAction* action = menu->addAction(title);
    actionToNode[action] = nodeCreator;
    return action;
}
