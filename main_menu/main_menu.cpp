#include "main_menu.h"

MainMenu::MainMenu(QWidget *widget)
	: QMenu(widget)
{
	this->createActions();
	this->translateActions();

	this->setObjectName("menu");

    connect(this->action_about_us,SIGNAL(triggered(bool)),this,SIGNAL(showAboutDialog()));
    connect(this->action_setting,SIGNAL(triggered(bool)),this,SIGNAL(showSettingPannelWidget()));
}

void MainMenu::createActions()
{
	//创建菜单项
	action_setting = new QAction(this);
    //action_new_character = new QAction(this);
    action_new_features =  new QAction(this);
	action_check_update = new QAction(this);
	action_change_company = new QAction(this);
	action_help_online = new QAction(this);
	action_platform_help = new QAction(this);
	action_login_home = new QAction(this);
	action_protect = new QAction(this);
	action_about_us = new QAction(this);

	//添加菜单项
	this->addAction(action_setting);
    //this->addAction(action_new_character);
    this->addAction(action_new_features);
    this->addAction(action_check_update);
	this->addAction(action_change_company);
	this->addSeparator();
	this->addAction(action_help_online);
	this->addAction(action_platform_help);
	this->addAction(action_login_home);
	this->addAction(action_protect);
	this->addAction(action_about_us);

    //QString::number将数字转换成字符串
    //QString QString::number ( long n, int base = 10 ) [static]
    //这是一个静态函数，它另外还有6个重载，这里不罗列了，这个函数可以把一个数字以某种进制格式化为一个QString返回，上面的问题中就已经用代码展示了。
    action_help_online->setObjectName(QString::number(HELP_ONLINE, 10));
    action_platform_help->setObjectName(QString::number(PLATFORM_HELP, 10));
    action_login_home->setObjectName(QString::number(LOGIN_HOME, 10));
    action_protect->setObjectName(QString::number(PROTECT, 10));

	//设置信号连接
//	connect(action_setting, SIGNAL(triggered()), this, SIGNAL(showSettingDialog()));
//	connect(action_new_character, SIGNAL(triggered()), this, SIGNAL(showNewCharacter()));
//	connect(action_about_us, SIGNAL(triggered()), this, SIGNAL(showAboutUs()));
    connect(action_help_online, SIGNAL(triggered()), this, SLOT(showPage()));
    connect(action_platform_help, SIGNAL(triggered()), this, SLOT(showPage()));
    connect(action_login_home, SIGNAL(triggered()), this, SLOT(showPage()));
    connect(action_protect, SIGNAL(triggered()), this, SLOT(showPage()));
}

void MainMenu::translateActions()
{
    action_setting->setText(QStringLiteral("设置"));
    //action_new_character->setText(tr("new character"));
    action_new_features->setText(QStringLiteral("新版特性"));
    action_check_update->setText(QStringLiteral("更新"));
    action_change_company->setText(QStringLiteral("切换到企业版"));
    action_help_online->setText(QStringLiteral("在线帮助"));
    action_platform_help->setText(QStringLiteral("论坛求助"));
    action_login_home->setText(QStringLiteral("登录"));
    action_protect->setText(QStringLiteral("隐私"));
    action_about_us->setText(QStringLiteral("关于"));
}

void MainMenu::showPage()
{
    QObject *object = QObject::sender();
    QAction *action = qobject_cast<QAction *>(object);
    QString object_name = action->objectName();
    int index = object_name.toInt();
    QString page;
    switch(index)
    {
    case HELP_ONLINE:
        page = QString("http://bbs.360.cn/cms/guide.html");
        break;

    case PLATFORM_HELP:
        page = QString("http://bbs.360safe.com/forum.php?mod=forumdisplay&fid=100");
        break;

    case LOGIN_HOME:
        page = QString("http://www.360.cn/");
        break;

    case PROTECT:
        page = QString("http://www.360.cn/privacy/v2/index.html");
        break;

    default:
        break;
    }

     QUrl url(page);
     QDesktopServices::openUrl(url);
}

void MainMenu::changeEvent(QEvent *event)
{
    QMenu::changeEvent(event);

//    if(event->type() == QEvent::LanguageChange)
//    {
//        //
//        translateActions();
//    }
}
