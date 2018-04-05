#include "login_widget.h"

LoginWidget::LoginWidget(QWidget *parent) : DraggableWidget(parent)
{
    this->setFixedWidth(MAIN_WINDOW_WIDTH);
    this->setFixedHeight(MAIN_WINDOW_HEIGHT);

//    this->setAttribute(Qt::WA_QuitOnClose,true);
//    this->setAttribute(Qt::WA_DeleteOnClose,true);

    //设置任务栏显示图标
    this->setWindowIcon(QIcon(QStringLiteral(":/resources/All_logo32-xp.ico")));

    this->setupUi();
    this->retranslateUi();

    m_is_login = false;

    //限制性验证
    this->validate();

    //初始化数据成员
    this->initialize();

//    QShortcut *key=new QShortcut(QKeySequence(Qt::Key_Return),this);//创建一个快捷键"Key_Return"键
//    connect(key,SIGNAL(activated()),this,SLOT(onCommitLogin));//连接到指定槽函数
//    QShortcut *key_enter=new QShortcut(QKeySequence(Qt::Key_Enter),this);//创建一个快捷键"Key_Return"键
//    connect(key_enter,SIGNAL(activated()),this,SLOT(onCommitLogin));//连接到指定槽函数
    //
    connect(m_title_widget,SIGNAL(showMinimize()),this,SLOT(showMinimized()));//最小化
//    connect(m_title_widget,SIGNAL(closeWidget()),this,SLOT(close()));//退出程序
    connect(m_title_widget,SIGNAL(closeWidget()),qApp,SLOT(quit()));//使用这种退出程序会，会导致登录窗体要点击两次关闭按钮才能退出


    connect(m_register_account_btn,SIGNAL(clicked(bool)),SLOT(onRegisterAccount()));//注册帐户
    connect(m_retrieve_password_btn,SIGNAL(clicked(bool)),this,SLOT(onRetrievePassword()));//忘记密码

    connect(this->m_user_name_le,SIGNAL(textChanged(const QString &)),this,SLOT(onUserNameLineEditValueChanged(const QString &)));

    connect(m_is_remember_password,SIGNAL(stateChanged(int)),this,SLOT(onIsRememberPasswordValueChanged(int)));//是否记住密码
    connect(m_is_auto_login,SIGNAL(stateChanged(int)),this,SLOT(onIsAutoLoginValueChanged(int)));//是否自动登录


    connect(this->m_submit_btn,SIGNAL(clicked(bool)),this,SLOT(onCommitLogin()));


    QList<QString> list;

//    //载入插件
//    if(!Utils::SettingsUtils::load_plugin(m_network_info_plugin_interface))//!load_plugin()
//    {
//        //如果无法加载插件
//        QMessageBox::information(this,"Error","Could not load the plugin");

//    }


    //将准点设置为用户输入框
    this->m_user_name_le->setFocus();

    //保存主窗体位置信息
    this->save_widget_position();
    //保存用户操作系统信息
    this->save_current_user_operate_system_info();


}

LoginWidget::~LoginWidget()
{
}

void LoginWidget::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("MainWidget"));

    m_main_fame_v_layout = new QVBoxLayout(this);
    m_main_fame_v_layout->setObjectName(QStringLiteral("m_main_fame_v_layout"));
    m_main_fame_v_layout->setSpacing(0);
    m_main_fame_v_layout->setContentsMargins(0,0,0,0);

    init_top_widget();

    m_main_fame_v_layout->addWidget(m_top_widget,0,Qt::AlignTop);

    init_center_widget();
    m_main_fame_v_layout->addWidget(m_center_widget,0,Qt::AlignHCenter|Qt::AlignTop);

    m_msg_widget = new QWidget(this);
    m_msg_widget->setObjectName(QStringLiteral("m_msg_widget"));
    m_msg_widget->setFixedHeight(28);
    m_msg_widget->setFixedWidth(this->width()-MAIN_PANNEL_RIGHT_MARGIN);
    m_msg_widget->setContentsMargins(0,0,0,0);

    m_main_fame_v_layout->addWidget(m_msg_widget,0,Qt::AlignHCenter|Qt::AlignTop);

    QHBoxLayout *msg_h_layout = new QHBoxLayout(m_msg_widget);
    msg_h_layout->setSpacing(0);
    msg_h_layout->setContentsMargins(0,0,0,0);

    //错误消息显示框
    m_err_msg_widget = new ErrorMessageWidget(m_msg_widget);
    m_err_msg_widget->setObjectName(QStringLiteral("m_err_msg_widget"));
    m_err_msg_widget->setFixedHeight(28);
    m_err_msg_widget->setFixedWidth(m_msg_widget->width());
    m_err_msg_widget->hide();

    msg_h_layout->addWidget(m_err_msg_widget,0,Qt::AlignTop);


    m_main_fame_v_layout->addStretch(0);

    init_bottom_widget();
    m_main_fame_v_layout->addWidget(m_bottom_widget,0,Qt::AlignLeft|Qt::AlignBottom);


}

void LoginWidget::retranslateUi()
{
    m_user_name_le->setPlaceholderText(QStringLiteral("邮箱帐号"));//c++标准
    m_password_le->setPlaceholderText(QStringLiteral("密码"));
    m_submit_btn->setText(QStringLiteral("登录"));

    m_is_remember_password->setText(QStringLiteral("记住密码"));
    m_is_auto_login->setText(QStringLiteral("自动登录"));
    m_register_account_btn->setText(QStringLiteral("注册帐户"));
    m_retrieve_password_btn->setText(QStringLiteral("忘记密码？"));
}

void LoginWidget::init_top_widget()
{
    m_top_widget = new QWidget();
    m_top_widget->setObjectName(QStringLiteral("m_top_widget"));
    m_top_widget->setFixedHeight(50);

    m_title_widget = new TitleWidget();
    m_title_widget->setObjectName(QStringLiteral("m_title_widget"));
    m_title_widget->setFixedHeight(26);

    QHBoxLayout *title_h_layout = new QHBoxLayout(m_top_widget);
    title_h_layout->setSpacing(0);
    title_h_layout->setContentsMargins(0,0,0,0);

    title_h_layout->addWidget(m_title_widget,0,Qt::AlignTop);

}

void LoginWidget::init_center_widget()
{
    m_center_widget = new QWidget();
    //m_center_widget->setObjectName(QStringLiteral("m_center_widget"));

    m_center_v_layout = new QVBoxLayout(m_center_widget);
    m_center_v_layout->setSpacing(0);
    m_center_v_layout->setObjectName(QStringLiteral("m_center_v_layout"));
    m_center_v_layout->setContentsMargins(0, 0, 0, 0);

    m_app_pictorial = new QLabel();
    m_app_pictorial->setObjectName(QStringLiteral("m_app_pictorial"));
    m_app_pictorial->setFixedHeight(150);

    m_center_v_layout->addWidget(m_app_pictorial,0,Qt::AlignHCenter|Qt::AlignTop);


    //登录部分
    //用户名
    m_user_name_le = new QLineEdit();
    m_user_name_le->setObjectName(QStringLiteral("m_user_name_le"));
    m_user_name_le->setFixedSize(190,30);

    m_center_v_layout->addWidget(m_user_name_le,0,Qt::AlignTop);

    //密码
    m_password_le = new PasswordLineEdit();//new QLineEdit();
    m_password_le->setObjectName(QStringLiteral("m_password_le"));
    m_password_le->setFixedSize(190,30);
    m_password_le->setEchoMode(QLineEdit::Password);//设置为密码模式

    m_center_v_layout->addWidget(m_password_le,0,Qt::AlignTop);


    //用于记住密码与自动登录处布局
    m_center_h_layout = new QHBoxLayout();
    m_center_h_layout->setSpacing(0);
    m_center_h_layout->setObjectName(QStringLiteral("m_center_h_layout"));
    m_center_h_layout->setContentsMargins(0, 10, 0, 15);

    //记住密码
    m_is_remember_password = new QCheckBox();
    m_is_remember_password->setObjectName(QStringLiteral("m_is_remember_password"));

    m_center_h_layout->addWidget(m_is_remember_password,0,Qt::AlignLeft);

    //自动登录
    m_is_auto_login = new QCheckBox();
    m_is_auto_login->setObjectName(QStringLiteral("m_is_auto_login"));

    m_center_h_layout->addWidget(m_is_auto_login,0,Qt::AlignRight);

    m_center_v_layout->addLayout(m_center_h_layout);

    //登录按钮
    m_submit_btn = new QPushButton();
    m_submit_btn->setObjectName(QStringLiteral("m_submit_btn"));
    m_submit_btn->setFixedSize(190,30);

    m_center_v_layout->addWidget(m_submit_btn,0,Qt::AlignBottom);

}


void LoginWidget::init_bottom_widget()
{
    m_bottom_widget = new QWidget();

    m_bottom_v_layout = new QVBoxLayout(m_bottom_widget);
    m_bottom_v_layout->setSpacing(0);
    m_bottom_v_layout->setObjectName(QStringLiteral("m_bottom_v_layout"));
    m_bottom_v_layout->setContentsMargins(20, 0, 0, 20);

    //注册帐户
    m_register_account_btn = new QPushButton();
    m_register_account_btn->setObjectName(QStringLiteral("m_register_account_btn"));
    m_register_account_btn->setCursor(Qt::PointingHandCursor);//将鼠标状态设置为手势

    m_bottom_v_layout->addWidget(m_register_account_btn,0,Qt::AlignBottom|Qt::AlignLeft);

    //忘记密码按钮
    m_retrieve_password_btn = new QPushButton();
    m_retrieve_password_btn->setObjectName(QStringLiteral("m_retrieve_password_btn"));
    m_retrieve_password_btn->setCursor(Qt::PointingHandCursor);//将鼠标状态设置为手势

//    m_retrieve_password_btn->setFixedSize(190,30);

    m_bottom_v_layout->addWidget(m_retrieve_password_btn,0,Qt::AlignBottom|Qt::AlignLeft);
}

void LoginWidget::initialize()
{
    m_str_user_name = m_user_name_le->text();
    m_str_password = m_password_le->text();
}


void LoginWidget::closeEvent(QCloseEvent *event)
{
    event->accept();
    emit this->onLoginRejected();

    DraggableWidget::closeEvent(event);
}

void LoginWidget::onRegisterAccount()
{
    QDesktopServices::openUrl(QUrl(QStringLiteral("http://www.sina.com.cn/")));

}


void LoginWidget::onRetrievePassword()
{
    QDesktopServices::openUrl(QUrl(QStringLiteral("http://www.sina.com.cn/")));

}

bool LoginWidget::save_widget_position()
{

    bool b_result = Utils::SettingsUtils::save_config_data_to_ini_file(Utils::APP_WIDGET_CONFIG_INI_FILE,
                                                                       "config","main_window_position_x",QString::number(this->pos().x()));

    if(b_result == false)
    {
        return false;
    }

    b_result = Utils::SettingsUtils::save_config_data_to_ini_file(Utils::APP_WIDGET_CONFIG_INI_FILE,
                                                             "config","main_window_position_y",QString::number(this->pos().y()));

    return b_result;
}


bool LoginWidget::save_current_user_operate_system_info()
{
    bool b_result = Utils::SettingsUtils::save_config_data_to_ini_file(Utils::USER_CURR_OS_INFO_CONFIG_INI_FILE,
                                                                       "sys_info","prettyProductName",QSysInfo::prettyProductName());
    if(b_result == false)
    {
        return false;
    }

    b_result = Utils::SettingsUtils::save_config_data_to_ini_file(Utils::USER_CURR_OS_INFO_CONFIG_INI_FILE,
                                                                           "sys_info","productType",QSysInfo::productType());

    if(b_result == false)
    {
        return false;
    }

    b_result = Utils::SettingsUtils::save_config_data_to_ini_file(Utils::USER_CURR_OS_INFO_CONFIG_INI_FILE,
                                                                           "sys_info","productVersion",QSysInfo::productVersion());

    if(b_result == false)
    {
        return false;
    }

    b_result = Utils::SettingsUtils::save_config_data_to_ini_file(Utils::USER_CURR_OS_INFO_CONFIG_INI_FILE,
                                                                           "sys_info","WindowsVersion",QString::number(QSysInfo::windowsVersion()));
    if(b_result == false)
    {
        return false;
    }

    b_result = Utils::SettingsUtils::save_config_data_to_ini_file(Utils::USER_CURR_OS_INFO_CONFIG_INI_FILE,
                                                                           "sys_info","machineHostName",QSysInfo::machineHostName());



    return b_result;
}

void LoginWidget::onUserNameLineEditValueChanged(const QString &str)
{
    if(str != this->m_str_user_name ){
        this->m_password_le->clear();
    }

    this->m_str_user_name = str;

}

void LoginWidget::onIsRememberPasswordValueChanged(int i)
{
    Utils::SettingsUtils::save_config_data_to_ini_file(Utils::APP_WIDGET_CONFIG_INI_FILE,
                                                                 "config","IsRememberPassword",QString::number(i));

}

void LoginWidget::onIsAutoLoginValueChanged(int i)
{
    //如果自动登录为选中状态，则将记住密码QCheckBox控件置为选中状态
    if(m_is_auto_login->checkState() == Qt::Checked)
    {
        m_is_remember_password->setChecked(true);
    }

    Utils::SettingsUtils::save_config_data_to_ini_file(Utils::APP_WIDGET_CONFIG_INI_FILE,
                                                                 "config","IsAutoLogin",QString::number(i));

}

bool LoginWidget::onCommitLogin()
{
    this->m_str_user_name = this->m_user_name_le->text().trimmed();
    this->m_str_password = this->m_password_le->text().trimmed();

    if(this->m_str_user_name.isEmpty() )
    {
        m_err_msg_widget->showInfomation(QStringLiteral("请输入用户名！"));
        if(m_err_msg_widget->isHidden())
        {
            m_err_msg_widget->show();
        }
        this->m_user_name_le->setFocus();
        return false;
    }

    if(this->m_str_password.isEmpty() )
    {
        m_err_msg_widget->showInfomation(QStringLiteral("请输入密码！"));
        if(m_err_msg_widget->isHidden())
        {
            m_err_msg_widget->show();
        }
        this->m_password_le->setFocus();
        return false;
    }

    if(this->m_str_user_name =="123" && this->m_str_password == "123")
    {

        //登录验证成功后，如果先前有错误信息提示，则隐藏
        if(m_err_msg_widget->isVisible())
        {
            m_err_msg_widget->hide();
        }
        //用户名与密码验证成功后，窗体暂停5秒然后进入主窗体
        m_center_widget->setEnabled(false);
        m_submit_btn->setText(QStringLiteral("登录中..."));
        QEventLoop eventloop;
        QTimer::singleShot(5000, &eventloop, SLOT(quit()));
        eventloop.exec();

        //登录验证成功，发射成功信号
        emit onLoginAccepted();
        return true;
    }else
    {
        m_err_msg_widget->showWarning(QStringLiteral("用户名或密码错误，登录失败！"));
        if(m_err_msg_widget->isHidden())
        {
            m_err_msg_widget->show();
        }
        this->m_user_name_le->clear();
        this->m_password_le->clear();
    }

    return false;

}

void LoginWidget::onLoginAccepted()
{

    return this->done(QDialog::Accepted);
}

void LoginWidget::onLoginRejected()
{
    return this->done(QDialog::Rejected);
}

void LoginWidget::onHideErrorMessageWidget()
{
    this->m_err_msg_widget->hide();
}

void LoginWidget::validate()
{
    //邮箱，参考http://blog.csdn.net/make164492212/article/details/51656638
    QRegExp rx(QStringLiteral("^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\\.[a-zA-Z0-9_-]+)+$"));
    QValidator *validator = new QRegExpValidator(rx, this);
    this->m_user_name_le->setValidator(validator);
}

void LoginWidget::keyPressEvent(QKeyEvent *event)
{
    DraggableWidget::keyReleaseEvent(event);

    //Qt中的回车键对应的是两个键值： Qt::Key_Enter  以及 Qt::Key_Return
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        onCommitLogin();
    }
}

