/*!
  *@file
  *@brief
  *@author
  *@date
  */

#ifndef CENTERWIDGET_H
#define CENTERWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QtCore>
#include <QStackedWidget>
#include <QListView>
#include <QListWidget>
#include "tool_button.h"

#include <QtWebEngineWidgets>
#include <QWebEngineView>



class CenterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CenterWidget(QWidget *parent = 0);
private:

    //主窗体
    QVBoxLayout *m_main_v_layout;//主布局
    QHBoxLayout *m_button_h_layout;//Tab按钮布局


    //tab面板
    QWidget *m_tab_bar_wdiget;//顶部tab面板
    QButtonGroup *m_tab_button_group;//按钮分组

    ToolButton *m_contact_tbtn;//联系人
    ToolButton *m_group_tbtn;//群聊
    ToolButton *m_app_tbtn;//应用
    ToolButton *m_mobile_tbtn;//手机
    ToolButton *m_history_tbtn;//会话历史

    QStackedWidget *m_stacked_widget;

    //中间主要的几大块
    QWidget *m_contact_tab;//联系人

    QWidget *m_group_tab;//群聊

    QWidget *m_app_tab;//应用

    QWidget *m_mobile_tab;//手机
    QWebEngineView *m_p_mobile_tab_web_view;

    QWidget *m_history_tab;//会话历史

    //各tab page
    //contact
    QVBoxLayout *m_contact_v_layout;
    QListWidget *m_contact_list_widget;
    //group
    QVBoxLayout *m_group_v_layout;

    //app
    QVBoxLayout *m_app_v_layout;

    //mobile
    QVBoxLayout *m_mobile_v_layout;

    //history
    QVBoxLayout *m_history_v_layout;



private:
    void setupUi();
    void retranslateUi();

    void init_tab_widget();//初始化TabWidget

    void init_tab_bar_widget();//初始化TabWidget的TabBar
    void init_tab_page_widget();//初始化TabWidget的TabPage

    void init_contact_tab();
    void init_group_tab();
    void init_app_tab();
    void init_mobile_tab();
    void init_history_tab();

};

#endif // CENTERWIDGET_H
