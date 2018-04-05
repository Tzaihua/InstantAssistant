/*!
  *@file
  *@brief   基本设置面板tab page
  *@author  Tzaihua
  *@date    2016-12-27
  */

#ifndef BASICSETTINGTABPAGEWIDGET_H
#define BASICSETTINGTABPAGEWIDGET_H

#include <QWidget>
#include <QObject>
#include <QListWidget>
#include <QListWidgetItem>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QMessageBox>
#include <QListIterator>

#include "global_constant.h"

#include "settings_utils.h"  //工具类
using namespace Baijuhua;
using namespace Utils;

class BasicSettingTabPageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BasicSettingTabPageWidget(QWidget *parent = 0);
    ~BasicSettingTabPageWidget();
    void setupUi();
    void retranslateUi();

protected:
    bool eventFilter(QObject * watched, QEvent * event);

private:
    QHBoxLayout *m_main_h_layout;

    //左侧分类列表
    QListWidget *m_left_category_list_widget;
    //右侧具体设置的显示区域
    QScrollArea *m_right_setting_scroll_area;
    QWidget *m_scroll_contents_widget;

    //----------------登录设置页--begin-------------------------------
    QWidget *m_login_setting_widget;//登录设置页
    QHBoxLayout *m_ls_main_h_layout;//横向布局
    QVBoxLayout *m_ls_setting_v_layout;//右侧具体设置垂直布局
    QLabel *m_ls_category_lbl;//登录标题
    QCheckBox *m_ls_auto_start_chk;//自动启动
    QCheckBox *m_ls_open_login_prompt_chk;//总是打开登录提示
    QCheckBox *m_ls_subscribe_to_daily_info_chk;//订阅每日资讯

    //----------------登录设置页--end---------------------------------



    //----------------主面板设置页--begin-------------------------------
    QWidget *m_main_pannel_setting_widget;//主面板设置页
    QHBoxLayout *m_mps_main_h_layout;//横向布局
    QVBoxLayout *m_mps_setting_v_layout;//右侧具体设置垂直布局
    QLabel *m_mps_category_lbl;//主面板标题

    QCheckBox *m_mps_display_at_the_front_chk;//始终保持在最前端

    QCheckBox *m_mps_auto_hide_when_docked_on_desktop_edge_chk;//停靠在桌面边缘时自动隐藏

    QCheckBox *m_mps_show_icon_in_taskbar_notification_area_chk;//在任务栏通知区域显示图标

    QLabel *m_mps_close_main_pannel_intro_lbl;//关闭主面板时
    QCheckBox *m_mps_quit_chk;//退出程序
    QCheckBox *m_mps_hide_to_taskbar_chk;//隐藏到任务栏



    //----------------主面板设置页--end---------------------------------


    //----------------提醒设置页--begin---------------------------------
    QWidget *m_remind_settting_widget;//提醒设置页
    QHBoxLayout *m_ms_main_h_layout;//横向布局
    QVBoxLayout *m_ms_setting_v_layout;//右侧具体设置垂直布局
    QLabel *m_ms_category_lbl;//提醒标题

    QCheckBox *m_ms_session_msg_chk;//会话消息提醒

    QCheckBox *m_ms_android_device_conn_chk;//Android设置连接提醒
    QLabel *m_ms_android_device_conn_intro_lbl;//Android设置连接提醒说明

    //----------------提醒设置页--end---------------------------------



    //----------------软件更新设置页--begin---------------------------------
    QWidget *m_app_update_setting_widget;//软件更新设置页
    QHBoxLayout *m_aus_main_h_layout;//横向布局
    QVBoxLayout *m_aus_setting_v_layout;//右侧具体设置垂直布局
    QLabel *m_aus_category_lbl;//标题

    QLabel *m_aus_update_mode_title_lbl;//软件更新方式

    QRadioButton *m_aus_auto_update_rbtn;//有更新时自动为我安装（推荐）
    QLabel *m_aus_auto_update_intro_lbl;//有更新时自动为我安装--说明

    QRadioButton *m_aus_manual_update_rbtn;//有更新时不安装，但提醒我
    QLabel *m_aus_manual_update_intro_lbl;//有更新时不安装，但提醒我---说明


    //----------------软件更新设置页--begin---------------------------------



private:


    void init_left_category_list_widget_data();

    void init_login_setting_widget();
    void init_main_pannel_setting_widget();
    void init_remind_settting_widget();
    void init_app_update_setting_widget();

signals:

public slots:
    void onScrollAreaValueChanged(int value);
    void onListWidgetItemClicked(QListWidgetItem  *item);
};

#endif // BASICSETTINGTABPAGEWIDGET_H
