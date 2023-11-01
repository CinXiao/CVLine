#ifndef CHANNELSEPARATION_H
#define CHANNELSEPARATION_H
#include "src/NodeGraphics/node.h"

#include <QImage>
class ChannelSeparation:public Node
{
public:
    ChannelSeparation(QPointF pos);
    void  paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QImage Image;
    void execute();
};

#endif // CHANNELSEPARATION_H
