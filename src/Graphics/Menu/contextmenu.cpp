#include "contextmenu.h"




ContextMenu::ContextMenu(QWidget *parent):QMenu(parent)
{

   StartAction =addAction("开始");

   DataMenu=new QMenu("数据");
   FunctionMenu=new QMenu("计算");
   ProgramControlMenu=new QMenu("控制");
   BooleanMenu=new QMenu("布尔逻辑");

   addMenu(ProgramControlMenu);
   addMenu(DataMenu);
   addMenu(FunctionMenu);
   addMenu(BooleanMenu);
    //程序控制项
    IfAction= ProgramControlMenu->addAction("IF");


   //数据菜单项
   IntAction= DataMenu->addAction("整数");
   DoubleAction= DataMenu->addAction("小数");
   BoolAction=DataMenu->addAction("布尔");
   BitAction=DataMenu->addAction("比特");
   StringAction= DataMenu->addAction("字符串");



   //计算菜单项
   Add_IntAction=FunctionMenu->addAction("整数相加");
   Add_DoubleAction=FunctionMenu->addAction("小数相加");
   Add_StringAction=FunctionMenu->addAction("字符串相加");

   Sub_IntAction=FunctionMenu->addAction("整数相减");
   Sub_DoubleAction=FunctionMenu->addAction("小数相减");


   AndAction=BooleanMenu->addAction("与");
   OrAction=BooleanMenu->addAction("或");
   NoAction=BooleanMenu->addAction("非");
   NotOrAction=BooleanMenu->addAction("异或");
   SOrAction=BooleanMenu->addAction("同或");
   NoAndAction=BooleanMenu->addAction("与非");
   NoOrAction=BooleanMenu->addAction("或非");
}

Node *ContextMenu::GetSelectedNode(QAction *action,QPointF pos)
{
    Node *node{nullptr};

    //控制节点
    if(action==IfAction)
    {
        node=new If(pos);
    }
    else if(action==StartAction)
    {
        node=new StartNode(pos);
        action->setEnabled(false);
    }
    //数据节点
    else if(action==IntAction)
    {
        node=new DataNode(pos,0,Port::Int);
    }else if(action==DoubleAction)
    {
        node=new DataNode(pos,0.0,Port::Double);
    }else if(action==StringAction)
    {
        node=new DataNode(pos,"",Port::String);
    }else if(action==BoolAction)
    {
        node=new DataNode(pos,false,Port::Bool);
    }else if(action==BitAction)
    {
        node=new DataNode(pos,0,Port::Bit);
    }
    //功能节点
    else if(action==Add_IntAction)
    {
        node=new AddNode(pos,Port::Int);
    }else if(action==Add_DoubleAction)
    {
        node=new AddNode(pos,Port::Double);
    }else if(action==Add_StringAction)
    {
        node=new AddNode(pos,Port::String);
    }else if(action==Sub_IntAction)
    {
        node=new Subtract(pos,Port::Int);
    }else if(action==Sub_DoubleAction)
    {
        node=new Subtract(pos,Port::Double);
    }//逻辑运算
    else if(action==AndAction)
    {
        node=new Booleanlogic(pos,Booleanlogic::AND);
    }
    else if(action==OrAction)
    {
        node=new Booleanlogic(pos,Booleanlogic::OR);
    }
    else if(action==NoAction)
    {
        node=new Booleanlogic(pos,Booleanlogic::NO);
    }
    else if(action==NotOrAction)
    {
        node=new Booleanlogic(pos,Booleanlogic::XOR);
    }
    else if(action==SOrAction)
    {
        node=new Booleanlogic(pos,Booleanlogic::SOR);
    }
    else if(action==NoAndAction)
    {
        node=new Booleanlogic(pos,Booleanlogic::NOAND);
    }
    else if(action==NoOrAction)
    {
        node=new Booleanlogic(pos,Booleanlogic::NOOR);
    }


    return node;
}
