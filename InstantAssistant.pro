#-------------------------------------------------
#
# Project created by QtCreator 2016-12-14T16:03:55
#
#-------------------------------------------------
#自定义变量说明：
#   MY_PRO_DIR  项目顶层目录
MY_PRO_TOP_DIR = D:\code_aliyun
MY_PRO_DIR = $${MY_PRO_TOP_DIR}\INSTANT_ASSISTANT_TOOLKITS

QT       += core gui network sql
QT       += webenginewidgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


DESTDIR += $${MY_PRO_DIR}\bin
#UI_DIR  += $${MY_PRO_TOP_DIR}\build-app\
#RCC_DIR += $${MY_PRO_TOP_DIR}\build-app
#MOC_DIR += $${MY_PRO_TOP_DIR}\build-app
#OBJECTS_DIR += $${MY_PRO_TOP_DIR}\build-app

#源文件编码方式,注意，如果 CODECFORTR 没有定义，将找 DEFAULTCODEC，如果还没有定义，将找 CODEC。3个都没有定义的话，就采用latin1
#CODECFORTR = utf-8 #or gbk
#DEFAULTCODEC = utf-8
#CODEC = utf-8
#CODECFORSRC = utf-8

#TARGET = IA
TEMPLATE = app

#包含的其他pri文件（一般用于依赖库的添加)


#主面板
include ($$PWD\common_base\common_base.pri)
include ($$PWD\title_widget\title_widget.pri)
include ($$PWD\center_widget\center_widget.pri)
include ($$PWD\user_info_pannel\user_info_pannel.pri)
include ($$PWD\bottom_function_widget\bottom_function_widget.pri)

include ($$PWD\unread_msg_box_widget\unread_msg_box_widget.pri)
include ($$PWD\file_share_widget\file_share_widget.pri)
include ($$PWD\collection_widget\collection_widget.pri)
include ($$PWD\main_menu\main_menu.pri)


#功能件
include ($$PWD\app_manager_widget\app_manager_widget.pri)
include ($$PWD\msg_manager_widget\msg_manager_widget.pri)
include ($$PWD\setting_pannel_widget\setting_pannel_widget.pri)
include ($$PWD\system_tray_widget\system_tray_widget.pri)
include ($$PWD\mini_news_widget\mini_news_widget.pri)
include ($$PWD\weather_info_floating_widget\weather_info_floating_widget.pri)
include ($${MY_PRO_DIR}\includes\plugin_core_interface\plugin_core_interface.pri)

#登录面板
include ($$PWD\login_widget\login_widget.pri)


#第三方库
include ($$PWD\qxtglobalshortcut\qxtglobalshortcut.pri)

SOURCES += main.cpp\
        main_widget.cpp \
    about_dialog.cpp \
    instant_message_dialog.cpp

HEADERS  += main_widget.h \
    about_dialog.h \
    instant_message_dialog.h

FORMS    += mainwidget.ui


RESOURCES += \
    default.qrc

RC_FILE +=  resources/app.rc

#语言
TRANSLATIONS += \
    resources/instant_assistant_en_US.ts \
    resources/instant_assistant_zh_CN.ts

#unix|win32: LIBS += -L$$PWD/../../bin/ -lCTKCore

#INCLUDEPATH += $$PWD/../../bin
#DEPENDPATH += $$PWD/../../bin

#unix|win32: LIBS += -L$$PWD/../../bin/ -lCTKPluginFramework

#INCLUDEPATH += $$PWD/../../bin
#DEPENDPATH += $$PWD/../../bin

#include ($${MY_PRO_DIR}\includes\ctk\ctk.pri)
