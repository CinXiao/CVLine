#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include <QFont>
#include <QKeyEvent>
#include <QTextOption>
#include <QTextCursor>
#include <QTextDocument>
#include <QGraphicsTextItem>


#include <QGraphicsSceneWheelEvent>
#include <QPainter>


class TextInput : public QGraphicsTextItem
{



public:
    TextInput(QRectF rect,QVariant &dat,QGraphicsItem* parent = nullptr);
    TextInput(QRectF rect,QGraphicsItem* parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void wheelEvent(QGraphicsSceneWheelEvent *event)override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QVariant dat;
    QRectF rect;


};

#endif // TEXTINPUT_H
