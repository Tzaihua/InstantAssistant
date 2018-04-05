#ifndef SECRECYSETTINGTABPAGEWIDGET_H
#define SECRECYSETTINGTABPAGEWIDGET_H

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

class SecrecySettingTabPageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SecrecySettingTabPageWidget(QWidget *parent = 0);
    ~SecrecySettingTabPageWidget();
    void setupUi();
    void retranslateUi();

private:

    QHBoxLayout *m_main_h_layout;
    //左侧分类列表
    QListWidget *m_left_category_list_widget;
    //右侧具体设置的显示区域
    QScrollArea *m_right_setting_scroll_area;

    QWidget *m_scroll_contents_widget;

    //远程桌面设置
    QWidget *m_remote_desktop_setting_widget;
    QHBoxLayout *m_rds_main_h_layout;
    QLabel *m_rds_catetory_lbl;
    QVBoxLayout *m_rds_setting_v_layout;
    QCheckBox *m_rds_allow_remote_conn_chk;//允许远程桌面连接本计算机
    QCheckBox *m_rds_auto_accept_conn_req_chk;//自动接受连接请求（建议手动关闭windows自动睡眠和锁屏功能）

private:
    void init_remote_desktop_setting_widget();


signals:

public slots:
    void onScrollAreaValueChanged(int value);
    void onListWidgetItemClicked(QListWidgetItem  *item);
};

#endif // SECRECYSETTINGTABPAGEWIDGET_H
