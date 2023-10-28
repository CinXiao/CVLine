#include "mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QApplication>
#include<QFile>
#include<qstring.h>
#include<QLabel>
#include "Windows/nodeeditingwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    (new NodeEditingWindow())->show();





    return a.exec();
}
