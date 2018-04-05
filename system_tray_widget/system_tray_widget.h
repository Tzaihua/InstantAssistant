#ifndef SYSTEMTRAYWIDGET_H
#define SYSTEMTRAYWIDGET_H

#include <QObject>
#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QWidgetAction>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>


class SystemTrayWidget : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit SystemTrayWidget(QWidget *parent = 0);
    ~SystemTrayWidget();
    void setupUi();
    void retranslateUi();

private:
    void createActions();
    void addActions();

private:
    QMenu *m_tray_menu; //托盘菜单

    //中间的菜单
    QAction *m_action_open; //打开程序
    QAction *m_action_help_center; //帮助中心
    QAction *m_action_check_new_version; //检查更新
    QAction *m_action_update; //升级
    QAction *m_action_login; //用户登录
    QAction *m_action_logout; //退出

signals:
    void showMainWidget();

public slots:
    void onActivated(QSystemTrayIcon::ActivationReason reason);
};

#endif // SYSTEMTRAYWIDGET_H
