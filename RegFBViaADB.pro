QT += quick
QT += testlib

CONFIG += c++11 congsole

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    AppDefines.h \
    Processing/ImageProcessing.h \
    AppMain.h \
    AppEnums.h \
    Controller/MainController.h \
    Processing/ADBCommand.h \
    Controller/APICommunication.h \
    Processing/HttpRequestController.h

SOURCES += \
        main.cpp \
    Processing/ImageProcessing.cpp \
    AppMain.cpp \
    Controller/MainController.cpp \
    Processing/ADBCommand.cpp \
    Controller/APICommunication.cpp \
    Processing/HttpRequestController.cpp

RESOURCES +=

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


INCLUDEPATH += "$$_PRO_FILE_PWD_/../OpenCV-Library/install/include"


LIBS += \
    -L"$$_PRO_FILE_PWD_/../OpenCV-Library/install/x86/mingw/lib"\
    -lopencv_core410        \
    -lopencv_highgui410     \
    -lopencv_imgcodecs410   \
    -lopencv_imgproc410     \
    -lopencv_features2d410  \
    -lopencv_calib3d410



