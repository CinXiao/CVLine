#include "textinput.h"








TextInput::TextInput(QString str, QGraphicsItem *parent):QGraphicsTextItem(str,parent)
{
    setFlag(QGraphicsTextItem::ItemIsFocusable, true);
    setPos(4, 42); // 设置文本框位置
    setTextInteractionFlags(Qt::TextEditorInteraction); // 允许编辑文本
    setDefaultTextColor(Qt::white);

    // 创建一个 QTextOption 并设置 wrapMode
    QTextOption textOption;
    textOption.setWrapMode(QTextOption::NoWrap);
    QTextDocument *textdocment=new QTextDocument();
    textdocment->setTextWidth(50);
    textdocment->setMaximumBlockCount(10);
    textdocment->setDefaultTextOption(textOption);
    setDocument(textdocment);


}

void TextInput::keyPressEvent(QKeyEvent *event)
{

    qDebug()<<"textinput";
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        // Prevent line breaks
        event->accept();
        return;
    }
    QGraphicsTextItem::keyPressEvent(event);

}
