QT = core gui quick

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Application.cpp \
        Atom.cpp \
        AtomController.cpp \
        AtomListModel.cpp \
        AtomModel.cpp \
        AtomRenderer.cpp \
        AtomScene.cpp \
        Atoms.cpp \
        Clock.cpp \
        GameObject.cpp \
        GameRenderer.cpp \
        GameScene.cpp \
        MenuScene.cpp \
        Molecule.cpp \
        OpenGLBuffer.cpp \
        OpenGLProgram.cpp \
        OpenGLShader.cpp \
        OpenGLTexture.cpp \
        OpenGLTexture1D.cpp \
        OpenGLVertexArray.cpp \
        PortalItem.cpp \
        PortalRenderer.cpp \
        QuickItem.cpp \
        QuickRenderer.cpp \
        SinesRenderer.cpp \
        TransitionRenderer.cpp \
        TransitionScene.cpp \
        WarpRenderer.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Application.h \
    Atom.h \
    AtomController.h \
    AtomListModel.h \
    AtomModel.h \
    AtomRenderer.h \
    AtomScene.h \
    Atoms.h \
    Clock.h \
    GameObject.h \
    GameRenderer.h \
    GameScene.h \
    Latch.h \
    MenuScene.h \
    Molecule.h \
    OpenGLBuffer.h \
    OpenGLProgram.h \
    OpenGLShader.h \
    OpenGLTexture.h \
    OpenGLTexture1D.h \
    OpenGLVertexArray.h \
    PortalItem.h \
    PortalRenderer.h \
    QuickItem.h \
    QuickRenderer.h \
    SinesRenderer.h \
    TransitionRenderer.h \
    TransitionScene.h \
    WarpRenderer.h \
    singleton.h

RESOURCES += \
    glsl.qrc \
    qml.qrc
