#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include <QFont>
#include <QKeyEvent>
#include <QTextOption>
#include <QTextDocument>
#include <QGraphicsTextItem>




class TextInput : public QGraphicsTextItem
{

public:
    TextInput(QString str,QGraphicsItem* parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent* event) override;

};

#endif // TEXTINPUT_H
