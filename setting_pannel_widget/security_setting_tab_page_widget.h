/*!
  *@file
  *@brief   安全设置面板tab page
  *@author  Tzaihua
  *@date    2016-12-28
  *@reference http://blog.csdn.net/taiyang1987912/article/details/50187799
  */

#ifndef SECURITYSETTINGTABPAGEWIDGET_H
#define SECURITYSETTINGTABPAGEWIDGET_H

#include <QObject>
#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QCheckBox>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>
#include <QScrollBar>
#include <QDebug>

#include "global_constant.h"

class SecuritySettingTabPageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SecuritySettingTabPageWidget(QWidget *parent = 0);
    ~SecuritySettingTabPageWidget();
    void setupUi();
    void retranslateUi();

private:

    QHBoxLayout *m_main_h_layout;
    //左侧分类列表
    QListWidget *m_left_category_list_widget;
    //右侧具体设置的显示区域
    QScrollArea *m_right_setting_scroll_area;

    QWidget *m_scroll_contents_widget;

    //密码设置
    QWidget *m_password_setting_widget;
    QHBoxLayout *m_pws_main_h_layout;
    QLabel *m_pws_catetory_lbl;
    QVBoxLayout *m_pws_setting_v_layout;
    QLabel *m_pws_intro_lbl;
    QPushButton *m_pws_remember_password_btn;

    //消息记录设置
    QWidget *m_msg_setting_widget;
    QHBoxLayout *m_ms_main_h_layout;
    QLabel *m_ms_category_lbl;
    QVBoxLayout *m_ms_setting_v_layout;
    QCheckBox *m_ms_auto_syn_chk;
    QCheckBox *m_ms_auto_del_chk;

    //安全更新设置
    QWidget *m_security_update_setting_widget;
    QHBoxLayout *m_su_main_h_layout;
    QLabel *m_su_category_lbl;
    QVBoxLayout *m_su_setting_v_layout;
    QRadioButton *m_su_auto_update_rbtn;
    QRadioButton *m_su_manual_update_rbtn;

private:
    void init_password_setting_widget();
    void init_msg_setting_widget();
    void init_security_update_setting_widget();
signals:

public slots:
    void onScrollAreaValueChanged(int value);
    void onListWidgetItemClicked(QListWidgetItem  *item);
};

#endif // SECURITYSETTINGTABPAGEWIDGET_H
