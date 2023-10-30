#include "textinput.h"

#include <QGraphicsSceneWheelEvent>









TextInput::TextInput(QVariant& dat, QGraphicsItem *parent):QGraphicsTextItem(dat.toString(),parent)
{
    this->dat=dat;
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

    setPlainText(dat.toString());
}

void TextInput::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        event->accept();
        return;
    }
    QGraphicsTextItem::keyPressEvent(event);
}

void TextInput::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    if(dat.type()==QVariant::Int)
        setPlainText(QString::number(toPlainText().toInt()+1));
    if(dat.type()==QVariant::Double)
        setPlainText(QString::number(toPlainText().toFloat()+0.01f));
    if(dat.type()==QVariant::Bool)
    {
        if(dat.toBool())
        {
            setPlainText("True");
            dat=false;
        }else
        {
        setPlainText("False");
             dat=true;
        }

    }

    QGraphicsTextItem::wheelEvent(event);
}

void TextInput::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    // 获取文本光标
    QTextCursor cursor = textCursor();
    // 选择整个文本
    cursor.select(QTextCursor::Document);
    // 使用新的光标
    setTextCursor(cursor);

    event->accept();
}
