#include "contextmenu.h"

ContextMenu::ContextMenu(QWidget *parent):QMenu(parent)
{
    ProgramControlMenu = CreateSubMenu("控制");
    VarDataMenu=CreateSubMenu("变量");
    InputDataMenu = CreateSubMenu("输入");
    FunctionMenu = CreateSubMenu("计算");
    CompareMenu=CreateSubMenu("比较");
    BooleanMenu = CreateSubMenu("逻辑");
    ImageMenu = CreateSubMenu("图像");
    IOMenu=CreateSubMenu("输出");

    AddMenuItem(IOMenu, "打印输出", [](QPointF pos) { return new Print(pos); });

    GetImageMenu=ImageMenu->addMenu("输入");
    GetImageInfoMenu=ImageMenu->addMenu("信息");
    ImageoperateMenu=ImageMenu->addMenu("操作");
    ImageFilterMenu=ImageMenu->addMenu("滤镜");

    AddMenuItem(GetImageMenu, "选择图像", [](QPointF pos) { return new ImageNode(pos); });
    AddMenuItem(GetImageMenu, "选择目录图像", [](QPointF pos) { return new ReadImage(pos); });

    AddMenuItem(GetImageInfoMenu, "获取图像信息", [](QPointF pos) { return new GetImageInfo(pos); });
    AddMenuItem(ImageoperateMenu, "亮度对比度", [](QPointF pos) { return new ImageAdjustment(pos); });
    AddMenuItem(ImageoperateMenu, "二值化", [](QPointF pos) { return new Binarization(pos); });
    AddMenuItem(ImageoperateMenu, "通道分离", [](QPointF pos) { return new ChannelSeparation(pos); });
    AddMenuItem(ImageoperateMenu, "通道合并", [](QPointF pos) { return new ChannelMerging(pos); });
    AddMenuItem(ImageoperateMenu, "图像转换", [](QPointF pos) { return new ImageConversion(pos); });

    //滤镜
    AddMenuItem(ImageFilterMenu, "高斯模糊", [](QPointF pos) { return new GaussianBlur(pos); });




    //控制
    AddMenuItem(ProgramControlMenu, "开始", [](QPointF pos) { return new StartNode(pos); });
    AddMenuItem(ProgramControlMenu, "IF", [](QPointF pos) { return new If(pos); });
    AddMenuItem(ProgramControlMenu, "Then", [](QPointF pos) { return new Then(pos); });
    AddMenuItem(ProgramControlMenu, "Loop", [](QPointF pos) { return new Loop(pos); });
    SetterMenu=ProgramControlMenu->addMenu("Setter");
    GetterMenu=ProgramControlMenu->addMenu("Getter");
    AddMenuItem(SetterMenu, "整数Set", [](QPointF pos) { return new Setter(pos,Port::Int); });
    AddMenuItem(SetterMenu, "小数Set", [](QPointF pos) { return new Setter(pos,Port::Double); });
    AddMenuItem(SetterMenu, "字符串Set", [](QPointF pos) {return new Setter(pos,Port::String); });
    AddMenuItem(SetterMenu, "布尔Set", [](QPointF pos) { return new Setter(pos,Port::Bool); });

    AddMenuItem(GetterMenu, "整数Get", [](QPointF pos) { return new Getter(pos,Port::Int); });
    AddMenuItem(GetterMenu, "小数Get", [](QPointF pos) { return new Getter(pos,Port::Double); });
    AddMenuItem(GetterMenu, "字符串Get", [](QPointF pos) {return new Getter(pos,Port::String); });
    AddMenuItem(GetterMenu, "布尔Get", [](QPointF pos) { return new Getter(pos,Port::Bool); });

    //变量
    AddMenuItem(VarDataMenu, "整数", [](QPointF pos) { return new VarNode(pos, 0, Port::Int); });
    AddMenuItem(VarDataMenu, "小数", [](QPointF pos) { return new VarNode(pos, 0.0, Port::Double); });
    AddMenuItem(VarDataMenu, "布尔", [](QPointF pos) { return new VarNode(pos, false, Port::Bool); });
    AddMenuItem(VarDataMenu, "比特", [](QPointF pos) { return new VarNode(pos, 0, Port::Bit); });
    AddMenuItem(VarDataMenu, "字符串", [](QPointF pos) { return new VarNode(pos, "", Port::String); });



    AddMenuItem(InputDataMenu, "整数", [](QPointF pos) { return new DataNode(pos, 0, Port::Int); });
    AddMenuItem(InputDataMenu, "小数", [](QPointF pos) { return new DataNode(pos, 0.0, Port::Double); });
    AddMenuItem(InputDataMenu, "布尔", [](QPointF pos) { return new DataNode(pos, false, Port::Bool); });
    AddMenuItem(InputDataMenu, "比特", [](QPointF pos) { return new DataNode(pos, 0, Port::Bit); });
    AddMenuItem(InputDataMenu, "字符串", [](QPointF pos) { return new DataNode(pos, "", Port::String); });


    IntFunctionMenu=FunctionMenu->addMenu("整数");
    DoubleFunctionMenu=FunctionMenu->addMenu("小数");
    StringFunctionMenu=FunctionMenu->addMenu("字符串");


    AddMenuItem(IntFunctionMenu, "加", [](QPointF pos) { return new AddNode(pos,Port::Int); });
    AddMenuItem(IntFunctionMenu, "减", [](QPointF pos) { return new Subtract(pos, Port::Int); });
    AddMenuItem(IntFunctionMenu, "乘", [](QPointF pos) { return new Multiply(pos, Port::Int);});
    AddMenuItem(IntFunctionMenu, "除", [](QPointF pos) { return new Division(pos, Port::Int);});
    AddMenuItem(IntFunctionMenu, "取模", [](QPointF pos) { return new Mod(pos, Port::Int);});
    AddMenuItem(IntFunctionMenu, "Max", [](QPointF pos) { return new Max(pos, Port::Int);});
    AddMenuItem(IntFunctionMenu, "Min", [](QPointF pos) { return new Min(pos, Port::Int);});

    AddMenuItem(DoubleFunctionMenu, "加", [](QPointF pos) { return new AddNode(pos, Port::Double); });
    AddMenuItem(DoubleFunctionMenu, "减", [](QPointF pos) { return new Subtract(pos, Port::Double); });
    AddMenuItem(DoubleFunctionMenu, "乘", [](QPointF pos) { return new Multiply(pos, Port::Double);});
    AddMenuItem(DoubleFunctionMenu, "除", [](QPointF pos) { return new Division(pos, Port::Double);});
    AddMenuItem(DoubleFunctionMenu, "取模", [](QPointF pos) { return new Mod(pos, Port::Double);});
    AddMenuItem(DoubleFunctionMenu, "Max", [](QPointF pos) { return new Max(pos, Port::Double);});
    AddMenuItem(DoubleFunctionMenu, "Min", [](QPointF pos) { return new Min(pos, Port::Double);});

    IntCompareFunctionMenu=CompareMenu->addMenu("整数");
    DoubleCompareFunctionMenu=CompareMenu->addMenu("小数");
    StringCompareFunctionMenu=CompareMenu->addMenu("字符串");

    //整数比较
    AddMenuItem(IntCompareFunctionMenu, "等于", [](QPointF pos) { return new equal(pos,Port::Int); });
    AddMenuItem(IntCompareFunctionMenu, "小于", [](QPointF pos) { return new Compare::less(pos,Port::Int); });
    AddMenuItem(IntCompareFunctionMenu, "大于", [](QPointF pos) { return new greater(pos,Port::Int); });
    //小数比较
    AddMenuItem(DoubleCompareFunctionMenu, "等于", [](QPointF pos) { return new equal(pos,Port::Double); });
    AddMenuItem(DoubleCompareFunctionMenu, "小于", [](QPointF pos) { return new Compare::less(pos,Port::Double); });
   AddMenuItem(DoubleCompareFunctionMenu, "大于", [](QPointF pos) { return new greater(pos,Port::Double); });

    //逻辑运算
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
