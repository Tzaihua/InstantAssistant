#ifndef BOTTOMFUNCTIONWIDGET_H
#define BOTTOMFUNCTIONWIDGET_H

#include <QObject>
#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QSpacerItem>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

#include "common.h"

#include "function_button.h"

#include "app_manager_widget.h"

class BottomFunctionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BottomFunctionWidget(QWidget *parent = 0);

private:
    void setupUi();
    void retranslateUi();
private:
    QVBoxLayout *m_main_v_layout;
    QHBoxLayout *m_function_top_h_layout;

    QToolButton *m_weiyun_tbtn;//微云按钮
    QToolButton *m_app_mgr_tbtn;//应用管理器按钮
    QHBoxLayout *m_function_bottom_h_layout;
    FunctionButton *m_main_menu_tbtn;//主菜单按钮
    FunctionButton *main_app_setting_tbtn;//程序设置中心按钮
    FunctionButton *m_open_msg_mgr_tbtn;//消息管理器按钮
    FunctionButton *m_file_share_tbtn;//文件共享按钮
    FunctionButton *m_collection_tbtn;//收藏
    FunctionButton *m_open_app_center_tbtn;


signals:
    void showMainMenu();//主菜单
    void showAppManagerWidget();//应用管理器
    void showSettingPannelWidget();//设置中心
    void showMsgManagerWidget();//消息管理器
    void showFileShareWidget();//文件共享
    void showCollectionWidget();//收藏
public slots:


};

#endif // BOTTOMFUNCTIONWIDGET_H
