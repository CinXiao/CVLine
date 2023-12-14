#include "treemenu.h"

TreeMenu::TreeMenu(QWidget *parent) : QTreeWidget(parent)
{
    setDragEnabled(true);
    setAcceptDrops(true);
    setDragDropMode(QAbstractItemView::DragOnly);

    QTreeWidgetItem *dataCategory = new QTreeWidgetItem(this);
    dataCategory->setText(0, "数据");


}
