#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

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

//#include "common.h"
#include "global_constant.h"

class TitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TitleWidget(QWidget *parent = 0);
    void setupUi();
    void retranslateUi();

signals:
    void showMainMenu();//显示系统菜单
    void showMinimize();//最小化窗体
    void restoreWidgetSize();//最大化与常规窗口之间切换的信号
    void closeWidget();//退出系统

public slots:

private:
    QHBoxLayout *m_main_title_h_layout;//整个标题部分水平布局
    QLabel *m_logo_lbl;//软件logo
    QLabel *m_app_name_lbl;//软件名称
    QPushButton *m_main_menu_btn;//主菜单
    QPushButton *m_medal_btn;//勋章按钮
    QPushButton *m_min_btn;//最小化按钮

    QPushButton *m_close_btn;//关闭按钮
};

#endif // TITLEWIDGET_H
