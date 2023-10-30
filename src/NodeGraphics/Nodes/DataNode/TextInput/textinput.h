#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include <QFont>
#include <QKeyEvent>
#include <QTextOption>
#include <QTextCursor>
#include <QTextDocument>
#include <QGraphicsTextItem>




class TextInput : public QGraphicsTextItem
{

public:
    TextInput(QVariant &dat,QGraphicsItem* parent = nullptr);


protected:
    void keyPressEvent(QKeyEvent* event) override;
    void wheelEvent(QGraphicsSceneWheelEvent *event)override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
private:
    QVariant dat;


};

#endif // TEXTINPUT_H
