#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

#include <QWidget>

#include <QPluginLoader>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>
#include <QPoint>
#include <QPropertyAnimation>
#include <QApplication>
#include <QDesktopWidget>

//#include "common.h"
#include "global_constant.h"
#include "draggable_widget.h"
#include "title_widget.h"
#include "user_info_cover_widget.h"
#include "app_search_line_edit.h"
#include "center_widget.h"
#include "bottom_function_widget.h"

#include "main_menu.h"
#include "app_manager_widget.h"
#include "msg_manager_widget.h"
#include "setting_pannel_widget.h"
#include "system_tray_widget.h"

#include "unread_msg_box_widget.h"
#include "file_share_widget.h"
#include "collection_widget.h"

#include "about_dialog.h"
#include "instant_message_dialog.h"



#include "mini_news_widget.h" //迷你新闻弹出窗体
//#include "weather_info_floating_widget.h" //天气资讯对话框

#include "login_widget.h" //登录窗体


//#include "network_info_plugin_interface.h"


using namespace Baijuhua;

#include "qxtglobalshortcut.h"
#define REG_RUN "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"

class MainWidget : public DraggableWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    void setupUi();
    void retranslateUi();


protected:
//     void closeEvent(QCloseEvent *event);//关闭对话框时要做的事情
    virtual bool eventFilter(QObject *object, QEvent *event);//过滤事件，用于显示天气预报
    virtual void leaveEvent(QEvent *event);
    virtual void enterEvent(QEvent *event);
private:
    QVBoxLayout *m_main_fame_v_layout;//主窗体垂直布局

    QWidget *m_top_widget;//项部部件，用于将标题、用户信息部件纳入；
    QWidget *m_search_bar_widget;//搜索工具栏部件
    CenterWidget *m_center_widget;

    QStackedWidget *m_center_stacked_widget;//用于在点击搜索框时，弹出搜索下拉栏
    QWidget *m_search_result_widget;//搜索下拉栏

    QWidget *m_bottom_widget;//顶部部件
    TitleWidget *m_title_widget;//窗体顶部标题部件

    QWidget *m_user_info_widget;//用户中心部件
    UserInfoCoverWidget *m_user_info_cover_widget;//用户中心封面部件

    AppSearchLineEdit *m_search_app_line_edit;

    BottomFunctionWidget *m_bottom_function_widget;//主面板底部功能区

    //功能部件
    MainMenu *m_main_menu;//主菜单
    AppManagerWidget *m_app_manager_widget;//应用管理器
    MsgManagerWidget *m_msg_manager_widget;//消息管理器
    SettingPannelWidget  *m_setting_pannel_widget;//设置中心


    UnreadMsgBoxWidget *m_unread_msg_box_widget;//用户区消息盒子
    FileShareWidget *m_file_share_widget;//文件共享
    CollectionWidget *m_collection_widget;//收藏
    AboutDialog *m_about_dialog;//关于对话框


    //插件
    // NetworkInfoPluginInterface *m_network_info_plugin;

    //登录
    LoginWidget *m_login_widget;//登录窗体

    //---------登录成功后，需要初始化的
    SystemTrayWidget *m_system_tray_widget;//托盘菜单
    InstantMessageDialog *m_instant_msg_dialog;//左下角消息对话框
    MiniNewsWidget *m_mini_news_widget;//迷你新闻弹出窗体

    //--------登录成功后，暂时不需要初始化的
//    WeatherInfoFloatingWidget *m_weather_info_floating_widget;//天气对话框

private:
    void init_top_widget();// 初始化顶部部件
    void init_user_info_cover_widget();//初始化用户中心部件
    void init_search_bar_widget();//初始化搜索按钮部件
    void init_center_widget();//初始化中间部件部件
    void init_bottom_widget();//初始化底部工具部件

    //窗体靠边自动隐藏
    void isAutoHide();
    void hideWidget();
    void showWidget();

    //方向，用于自动隐藏窗体功能
    enum Direction
    {
        None,
        Up,
        Right,
        Down,
        Left
    };

    QPoint m_mouseMovePoint;
    bool m_bMousePressed;
    Direction m_enDriection;
    bool m_bIsAutoHide;

    int m_nDesktopWidth;

signals:
    void sendCurrentPos(QPoint);
    void showInstantMessageDialog(QString title, QString content);//显示右下角即时消息对话框

public slots:
    //-------底部工具栏
    void onShowMainMenu();//显示主菜单
    void onShowAppManagerWidget();//应用管理器
    void onShowMsgManagerWidget();//消息管理器
    void onShowSettingPannelWidget();//设置中心
    void onShowFileShareWidget();//文件共享
    void onShowCollectionWidget();//收藏

    //--------用户信息区工具栏
    void onShowUnreadMsgBoxWidget();//显示用户区的消息盒子

    void onShowAboutDialog();//显示关于对话框

    void onShowMainWidget();//显示主窗体


    //---------登录相关
    int onCreateLoginScreen();//
    void onCreateSystemScreen();//显示系统启动相关

    //---------天气
//    void onCreateWeatherInfoFloatingWidget();//创建天气对话框

    //设置随操作系统自动启动
    void set_auto_run_by_regedit(bool is_auto_run);

};

#endif // MAIN_WIDGET_H
