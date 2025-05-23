QT       += \
    core gui \
    multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/GameWindow.cpp \
    src/entities/Barrier.cpp \
    src/entities/Ledge.cpp \
    src/entities/NPC.cpp \
    src/entities/Player.cpp \
    src/entities/Tallgrass.cpp \
    src/entities/TownBox.cpp \
    src/scenes/BattleScene.cpp \
    src/scenes/GameOver.cpp \
    src/scenes/GrasslandScene.cpp \
    src/scenes/TitleScene.cpp \
    src/scenes/LaboratoryScene.cpp \
    src/core/ResourceManager.cpp \
    src/core/Scene.cpp \
    src/main.cpp \
    src/scenes/TownScene.cpp \
    src/ui/UIbag.cpp \
    src/ui/UIchoose.cpp \
    src/ui/UIdialog.cpp \
    src/util/ClickableTextItem.cpp

HEADERS += \
    src/GameWindow.h \
    src/entities/Barrier.h \
    src/entities/Ledge.h \
    src/entities/NPC.h \
    src/entities/Player.h \
    src/entities/Tallgrass.h \
    src/entities/TownBox.h \
    src/scenes/BattleScene.h \
    src/scenes/GameOver.h \
    src/scenes/GrasslandScene.h \
    src/scenes/TitleScene.h \
    src/scenes/LaboratoryScene.h \
    src/core/ResourceManager.h \
    src/core/Scene.h \
    src/scenes/TownScene.h \
    src/ui/UIbag.h \
    src/ui/UIchoose.h \
    src/ui/UIdialog.h \
    src/util/ClickableTextItem.h

FORMS +=

TRANSLATIONS += \
    ncku-cs2-113_zh_TW.ts

CONFIG += lrelease
CONFIG += embed_translations
CONFIG += sdk_no_version_check # 忽略版本檢查

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
