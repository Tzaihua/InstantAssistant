/*!
  *@file
  *@brief   设置面板
  *@author  Tzaihua
  *@date    2016-12-27
  */

#ifndef SETTINGPANNELWIDGET_H
#define SETTINGPANNELWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>
#include <QStackedWidget>
#include <QMouseEvent>
#include <QMessageBox>

#include "draggable_widget.h"
#include "global_constant.h"
#include "dialog_title_widget.h"

#include "basic_setting_tab_page_widget.h"
#include "security_setting_tab_page_widget.h"
#include "secrecy_setting_tab_page_widget.h"

class SettingPannelWidget : public DraggableWidget
{
    Q_OBJECT
public:
    explicit SettingPannelWidget(QWidget *parent = 0);
    ~SettingPannelWidget();
    void setupUi();
    void retranslateUi();

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    QVBoxLayout *m_main_v_layout;//整体垂直布局

    //Title区
    DialogTitleWidget *m_dialog_title_widget;//对话框顶部标题部分

    QWidget *m_title_widget;//标题部件
    QHBoxLayout *m_title_h_layout;//整个标题部分水平布局
    QLabel *m_logo_lbl;//软件logo
    QLabel *m_app_name_lbl;//软件名称
    QPushButton *m_min_btn;//最小化按钮
    QPushButton *m_close_btn;//关闭按钮

    //Tab面板区
    QWidget *m_tab_widget;//Tab Widget 控件
    QVBoxLayout *m_tab_widget_v_layout;//Tab Widget整体垂直布局
    QHBoxLayout *m_button_h_layout;//Tab按钮布局

    //tab面板
    QWidget *m_tab_bar_wdiget;//顶部tab bar面板
    QButtonGroup *m_tab_button_group;//按钮分组

    QToolButton *m_basic_setting_tbtn;//基本设置
    QToolButton *m_security_setting_tbtn;//安全设置
    QToolButton *m_secrecy_setting_tbtn;//隐私设置

    QStackedWidget *m_stacked_widget;

    QWidget *m_basic_setting_tab;//基本设置tab page
    QWidget *m_security_setting_tab;//安全tab page
    QWidget *m_secrecy_setting_tab;//隐私tab page

    //各Tab页
    BasicSettingTabPageWidget *m_basic_setting_tab_page_widget;

    SecuritySettingTabPageWidget *m_security_setting_tab_page_widget;

    SecrecySettingTabPageWidget *m_secrecy_setting_tab_page_widget;
private:
    void init_title_widget();//初始化顶部标题部件

    void init_tab_widget();//初始化TabWidget

    void init_tab_bar_widget();//初始化TabWidget的TabBar
    void init_tab_page_widget();//初始化TabWidget的TabPage

    void init_basic_setting_tab();
    void init_security_setting_tab();
    void init_secrecy_setting_tab();

signals:

public slots:
};

#endif // SETTINGPANNELWIDGET_H
