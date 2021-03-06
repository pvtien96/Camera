QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BaseHandler.cpp \
    BaseMessage.cpp \
    ByteBuffer.cpp \
    CameraHandler.cpp \
    CameraMessage.cpp \
    FrameMessage.cpp \
    HandleFactory.cpp \
    ManagerController.cpp \
    MessageFactory.cpp \
    config.cpp \
    configlib.cpp \
    imagesettings.cpp \
    main.cpp \
    camera.cpp \
    transporter.cpp \
    videosettings.cpp

HEADERS += \
    BaseHandler.h \
    BaseMessage.h \
    ByteBuffer.h \
    CameraHandler.h \
    CameraMessage.h \
    FrameMessage.h \
    HandleFactory.h \
    ManagerController.h \
    MessageFactory.h \
    camera.h \
    config.h \
    configlib.h \
    constant.h \
    imagesettings.h \
    transporter.h \
    videosettings.h

FORMS += \
    camera.ui \
    imagesettings.ui \
    videosettings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += camera.qrc

include($$[QT_INSTALL_EXAMPLES]/multimedia/shared/shared.pri)
