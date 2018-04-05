/*!
  *@file
  *@brief   主面板封面模式(用户信息显示)
  *@author  Tzaihua
  *@date    2016-12-22
  */

#ifndef USERINFOCOVERWIDGET_H
#define USERINFOCOVERWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QToolButton>

//#include <common.h>
#include "global_constant.h"
#include "function_button.h"
#include "signature_line_edit.h"


class UserInfoCoverWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UserInfoCoverWidget(QWidget *parent = 0);
    void setupUi();
    void retranslateUi();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual bool eventFilter(QObject *object, QEvent *event);
private:
    //主布局
    QVBoxLayout *m_main_v_layout;

    //水平顶部布局，不包含下面排app快捷启动按钮那行
    QHBoxLayout *m_main_top_h_layout;

    //用户信息左侧垂直布局,不包含右侧的天气按钮
    QVBoxLayout *m_user_info_left_v_layout;

    //用户信息水平布局，即，用户妮称，用户状态、等级按钮的布局
    QHBoxLayout *m_user_info_h_layout;


    QPushButton *m_user_nick_name_btn;//用户妮称
    QToolButton *m_status_tbtn;//用户状态
    QToolButton *m_user_grade_tbtn;//用户等级
    SignatureLineEdit *m_signature_line_edit;//用户签名
//    QLabel *m_weather_lbl;//天气

    QWidget *m_app_short_cut_widget;//快捷工具栏  
    QHBoxLayout *m_app_short_cut_h_layout;//快捷工具栏水平布局
    FunctionButton *m_user_space_tbtn;//用户空间快捷按钮
    FunctionButton *m_customer_center_tbtn;//
    FunctionButton *m_menu_help_tbtn;//
    FunctionButton *m_question_and_advance_tbtn;//

    FunctionButton *m_app_face_manager_tbtn;//皮肤管理快捷按钮
    FunctionButton *m_user_info_box_tbtn;//消息盒子快捷按钮
signals:
//    void showMsgManagerWidget();
    void showUnreadMsgBoxWidget();

public:
//        QLabel *m_weather_lbl;//天气

};

#endif // USERINFOCOVERWIDGET_H
