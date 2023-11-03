#ifndef CHANNELMERGING_H
#define CHANNELMERGING_H

#include"src/Utils/ImageConversionUtil.h"
#include "src/Graphics/NodeGraphics/node.h"
#include <QImage>
class ChannelMerging:public Node
{
public:
    ChannelMerging(QPointF pos);
    void  paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QImage redImage;
    QImage greenImage;
    QImage blueImage;
     void execute()override;
};

#endif // CHANNELMERGING_H
