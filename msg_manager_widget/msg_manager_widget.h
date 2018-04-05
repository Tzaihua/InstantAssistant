#ifndef MSGMANAGERWIDGET_H
#define MSGMANAGERWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>
#include <QStackedWidget>
#include "global_constant.h"
#include "draggable_widget.h"
#include "dialog_title_widget.h"

class MsgManagerWidget : public DraggableWidget
{
    Q_OBJECT
public:
    explicit MsgManagerWidget(QWidget *parent = 0);
    ~MsgManagerWidget();
    void setupUi();
    void retranslateUi();

private:
    DialogTitleWidget *m_dialog_title_widget;//对话框顶部标题部分
    QVBoxLayout *m_main_v_layout;//整体垂直布局

    //Tab面板区
    QWidget *m_tab_widget;//Tab Widget 控件
    QVBoxLayout *m_tab_widget_v_layout;//Tab Widget整体垂直布局
    QHBoxLayout *m_button_h_layout;//Tab按钮布局

    //tab面板
    QWidget *m_tab_bar_wdiget;//顶部tab bar面板
    QButtonGroup *m_tab_button_group;//按钮分组

    QToolButton *m_contact_msg_tbtn;//联系人消息
    QToolButton *m_group_msg_tbtn;//群消息
    QToolButton *m_plugins_msg_tbtn;//插件消息
    QToolButton *m_sys_msg_tbtn;//系统消息
    QToolButton *m_mobile_msg_tbtn;//手机消息

    QStackedWidget *m_stacked_widget;

    QWidget *m_contact_msg_widget;//联系人消息   tab_page
    QWidget *m_group_msg_widget;//群消息   tab_page
    QWidget *m_plugins_msg_widget;//插件消息    tab_page
    QWidget *m_sys_msg_widget;//系统消息    tab_page
    QWidget *m_mobile_msg_widget;//手机消息 tab_page

private:
    void init_tab_widget();//初始化TabWidget

    void init_tab_bar_widget();//初始化TabWidget的TabBar
    void init_tab_page_widget();//初始化TabWidget的TabPage


signals:

public slots:
    void onShowMinimize();//最小化窗体
    void onCloseWidget();//关闭窗体
};

#endif // MSGMANAGERWIDGET_H
