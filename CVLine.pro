QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/Image/InAndOut/readimage.cpp \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/Image/channelmerging.cpp \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/Image/gaussianblur.cpp \
     src/Model/ConnectionModel/NodeManager.cpp \
     src/Graphics/Menu/contextmenu.cpp \
     src/Graphics/graphicsview.cpp \
     src/Graphics/LineGraphics/beziercurveitem.cpp \
     src/Graphics/NodeGraphics/Nodes/DataNode/ImageNode.cpp \
     src/Graphics/NodeGraphics/Nodes/DataNode/TextInput/textinput.cpp \
     src/Graphics/NodeGraphics/Nodes/DataNode/datanode.cpp \
     src/Graphics//NodeGraphics/Nodes/FunctionNodes/Calculate/Add.cpp \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/Calculate/Subtract.cpp \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/Conversion/convertion.cpp \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/Image/binarization.cpp \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/Image/channelseparation.cpp \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/Image/getimageinfo.cpp \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/Image/imageadjustment.cpp \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/Image/imageconversion.cpp \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/LogicOperation/Booleanlogic.cpp \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/ProgramControl/If.cpp \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/ProgramControl/then.cpp \
     src/Graphics/NodeGraphics/Nodes/startnode.cpp \
     src/Graphics/NodeGraphics/node.cpp \
     src/Windows/nodeeditingwindow.cpp \
     src/main.cpp \
     src/mainwindow.cpp

HEADERS += \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/Image/InAndOut/readimage.h \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/Image/channelmerging.h \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/Image/gaussianblur.h \
     src/Model/ConnectionModel/NodeManager.h \
     src/Entity/Relations/LineInfo.h \
     src/Entity/Relations/NodeInfo.h \
     src/Entity/Relations/PortInfo.h \
     src/Entity/Relations/StreamPortinfo.h \
     src/Graphics/Menu/contextmenu.h \
     src/Graphics/graphicsview.h \
     src/Graphics/LineGraphics/beziercurveitem.h \
     src/Graphics/NodeGraphics/Nodes/DataNode/ImageNode.h \
     src/Graphics/NodeGraphics/Nodes/DataNode/TextInput/textinput.h \
     src/Graphics/NodeGraphics/Nodes/DataNode/datanode.h \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/Calculate/Add.h \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/Calculate/Subtract.h \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/Conversion/convertion.h \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/Image/binarization.h \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/Image/channelseparation.h \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/Image/getimageinfo.h \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/Image/imageadjustment.h \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/Image/imageconversion.h \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/LogicOperation/Booleanlogic.h \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/ProgramControl/If.h \
     src/Graphics/NodeGraphics/Nodes/FunctionNodes/ProgramControl/then.h \
     src/Graphics/NodeGraphics/Nodes/startnode.h \
     src/Graphics/NodeGraphics/Port/Port.h \
     src/Graphics/NodeGraphics/node.h \
     src/Windows/nodeeditingwindow.h \
     src/Graphics/graphicsview.h \
     src/mainwindow.h

FORMS += \
     src/Windows/nodeeditingwindow.ui \
     ui/mainwindow.ui

INCLUDEPATH +=\
    opencv/opencv2\


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/opencv/lib/ -lopencv_world480
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/opencv/lib/ -lopencv_world480d


INCLUDEPATH += $$PWD/opencv
DEPENDPATH += $$PWD/opencv
