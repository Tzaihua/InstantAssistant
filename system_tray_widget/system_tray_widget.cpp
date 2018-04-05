#include "system_tray_widget.h"

SystemTrayWidget::SystemTrayWidget(QWidget *parent) : QSystemTrayIcon(parent)
{
    this->createActions();
    this->addActions();
    this->retranslateUi();

    connect(this,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(onActivated(QSystemTrayIcon::ActivationReason)));

}

SystemTrayWidget::~SystemTrayWidget()
{

}

void SystemTrayWidget::setupUi()
{

}

void SystemTrayWidget::createActions()
{
    //设置托盘项图标
    this->setIcon(QIcon(QStringLiteral(":/resources/All_logo32-xp.ico")));
    m_tray_menu = new QMenu();
    m_tray_menu->setFixedWidth(250);

    m_action_open = new QAction(this);
    m_action_help_center = new QAction(this);
    m_action_check_new_version = new QAction(this);
    m_action_update = new QAction(this);
    m_action_login = new QAction(this);
    m_action_logout = new QAction(this);



    //设置信号连接（这里仅列举连接显示窗口的信号）
    connect(m_action_open, SIGNAL(triggered()), this, SIGNAL(showMainWidget()));
    connect(m_action_logout, SIGNAL(triggered()), qApp, SLOT(quit()));

    this->setContextMenu(m_tray_menu);
}

void SystemTrayWidget::addActions()
{
    m_tray_menu->addAction(m_action_open);
    m_tray_menu->addAction(m_action_help_center);
    m_tray_menu->addSeparator();//分割线
    m_tray_menu->addAction(m_action_check_new_version);
    m_tray_menu->addAction(m_action_update);
    m_tray_menu->addSeparator();//分割线
    m_tray_menu->addAction(m_action_login);
    m_tray_menu->addAction(m_action_logout);

}

void SystemTrayWidget::retranslateUi()
{
    m_action_open->setText(QStringLiteral("打开"));
    m_action_help_center->setText(QStringLiteral("在线帮助"));
    m_action_check_new_version->setText(QStringLiteral("检查新版本"));
    m_action_update->setText(QStringLiteral("升级"));
    m_action_login->setText(QStringLiteral("登录"));
    m_action_logout->setText(QStringLiteral("退出"));
}

void SystemTrayWidget::onActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:

        break;
    case QSystemTrayIcon::DoubleClick:
        break;

    case QSystemTrayIcon::MiddleClick:

        break;

    case QSystemTrayIcon::Context:

        break;

    default:
        break;
    }
}
