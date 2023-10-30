QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
     src/ConnectionModel/NodeManager.cpp \
     src/Graphics/Menu/contextmenu.cpp \
     src/Graphics/graphicsview.cpp \
     src/LineGraphics/beziercurveitem.cpp \
     src/NodeGraphics/Nodes/DataNode/TextInput/textinput.cpp \
     src/NodeGraphics/Nodes/DataNode/datanode.cpp \
     src/NodeGraphics/Nodes/FunctionNodes/Calculate/Add.cpp \
     src/NodeGraphics/Nodes/FunctionNodes/Calculate/Subtract.cpp \
     src/NodeGraphics/Nodes/FunctionNodes/Conversion/convertion.cpp \
     src/NodeGraphics/Nodes/startnode.cpp \
     src/NodeGraphics/node.cpp \
     src/Windows/nodeeditingwindow.cpp \
     src/main.cpp \
     src/mainwindow.cpp

HEADERS += \
     src/ConnectionModel/NodeManager.h \
     src/ConnectionModel/Relations/LineInfo.h \
     src/ConnectionModel/Relations/NodeInfo.h \
     src/ConnectionModel/Relations/PortInfo.h \
     src/ConnectionModel/Relations/StreamPortinfo.h \
     src/Graphics/Menu/contextmenu.h \
     src/Graphics/graphicsview.h \
     src/LineGraphics/beziercurveitem.h \
     src/NodeGraphics/Nodes/DataNode/TextInput/textinput.h \
     src/NodeGraphics/Nodes/DataNode/datanode.h \
     src/NodeGraphics/Nodes/FunctionNodes/Calculate/Add.h \
     src/NodeGraphics/Nodes/FunctionNodes/Calculate/Subtract.h \
     src/NodeGraphics/Nodes/FunctionNodes/Conversion/convertion.h \
     src/NodeGraphics/Nodes/startnode.h \
     src/NodeGraphics/Port/Port.h \
     src/NodeGraphics/node.h \
     src/Windows/nodeeditingwindow.h \
     src/graphicsview.h \
     src/mainwindow.h

FORMS += \
     src/Windows/nodeeditingwindow.ui \
     ui/mainwindow.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
