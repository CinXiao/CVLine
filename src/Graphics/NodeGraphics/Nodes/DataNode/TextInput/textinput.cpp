#include "textinput.h"

#include <QRegularExpression>
#include <QRegularExpressionValidator>



TextInput::TextInput(QRectF rect,QVariant& dat, QGraphicsItem *parent):QGraphicsTextItem(dat.toString(),parent),rect(rect)
{
    this->dat=dat;
    setFlag(QGraphicsTextItem::ItemIsFocusable, true);
    setPos(rect.x(),rect.y()); // 设置文本框位置
    setTextInteractionFlags(Qt::TextEditorInteraction); // 允许编辑文本
    setDefaultTextColor(Qt::white);


    // 创建一个 QTextOption 并设置 wrapMode
    QTextOption textOption;
    textOption.setWrapMode(QTextOption::NoWrap);
    QTextDocument *textdocment=new QTextDocument();
    textdocment->setDefaultTextOption(textOption);
    setDocument(textdocment);
    QFont font;
    font.setPointSize(15); // 设置字体大小为 12
    font.setBold(true);
    setFont(font);
    setTextWidth(50);

    setPlainText(dat.toString());


}

TextInput::TextInput(QRectF rect, QGraphicsItem *parent):QGraphicsTextItem("",parent),rect(rect)
{
    setFlag(QGraphicsTextItem::ItemIsFocusable, true);
    setPos(rect.x(),rect.y()); // 设置文本框位置
    setTextInteractionFlags(Qt::TextEditorInteraction); // 允许编辑文本
    setDefaultTextColor(Qt::white);


    // 创建一个 QTextOption 并设置 wrapMode
    QTextOption textOption;
    textOption.setWrapMode(QTextOption::NoWrap);
    QTextDocument *textdocment=new QTextDocument();
    textdocment->setDefaultTextOption(textOption);
    setDocument(textdocment);
    QFont font;
    font.setPointSize(15); // 设置字体大小为 12
    font.setBold(true);
    setFont(font);
    setTextWidth(50);
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

    int fundamentalval;
    if (event->delta() > 0)
        fundamentalval=1;
    else
         fundamentalval=-1;

    if(dat.type()==QVariant::Int)
        setPlainText(QString::number(toPlainText().toInt()+1*fundamentalval));
    if(dat.type()==QVariant::Double)
        setPlainText(QString::number(toPlainText().toFloat()+0.01f*fundamentalval));
    if(dat.type()==QVariant::Bool)
    {
            setPlainText(dat.toString());
            dat=!dat.toBool();
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

void TextInput::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setPen(Qt::NoPen);
    QRectF backgroundRect(0,0,std::max(rect.width(),document()->size().width()),rect.height());
    painter->setBrush(QBrush(QColor(30, 30, 30,100))); // 设置底色
    painter->drawRoundedRect(backgroundRect,5,5);
    QGraphicsTextItem::paint(painter,option,widget);
}
