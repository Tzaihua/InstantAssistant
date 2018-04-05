/*!
  *@file
  *@brief   各对话框的标题抬头部分，用作公用
  *@author  Tzaihua
  *@date    2017-01-24
  */

#ifndef DIALOG_TITLE_WIDGET_H
#define DIALOG_TITLE_WIDGET_H

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
#include <QSpacerItem>

#include "global_constant.h"


class DialogTitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DialogTitleWidget(QWidget *parent = 0);
    void setupUi();
    void retranslateUi();

    //对话框标题
    Q_PROPERTY(QString DialogTitle READ getDialogTitle WRITE setDialogTitle NOTIFY DialogTitleChanged DESIGNABLE true)

    //最小化按钮，可视状态改变信号
    Q_PROPERTY(bool VisualStatusForMinimizeBtn READ isVisualForMinimizeBtn WRITE setVisualStatusForMinimizeBtn NOTIFY VisualStatusForMinimizeBtnChanged DESIGNABLE true)


    //对话框标题
    QString getDialogTitle() const;
    void setDialogTitle(const QString title);

    //最小化按钮是否可视
    bool isVisualForMinimizeBtn() const;
    void setVisualStatusForMinimizeBtn(const bool isVisual);

private:
    QHBoxLayout *m_main_title_h_layout;//整个标题部分水平布局
    QLabel *m_logo_lbl;//软件logo
    QLabel *m_app_name_lbl;//软件名称
    QPushButton *m_main_menu_btn;//主菜单
    QPushButton *m_medal_btn;//勋章按钮
    QPushButton *m_min_btn;//最小化按钮
    //QPushButton *m_chanage_btn;//最大化与正常尺寸之间切换
    QPushButton *m_close_btn;//关闭按钮

private:
    bool m_is_visual_for_minimize_btn = true;//最小化按钮是否可显示

signals:
    void showMainMenu();//显示系统菜单
    void showMinimize();//最小化窗体
    void restoreWidgetSize();//最大化与常规窗口之间切换的信号
    void closeWidget();//退出系统
    void DialogTitleChanged(const QString title);
    void VisualStatusForMinimizeBtnChanged(const bool isVisual);//最小化按钮，可视状态改变信号

public slots:


};

#endif // DIALOG_TITLE_WIDGET_H
