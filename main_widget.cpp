#include "main_widget.h"


MainWidget::MainWidget(QWidget *parent) :
    DraggableWidget(parent)
  ,m_mouseMovePoint(0, 0)
  ,m_bMousePressed(false)
  ,m_enDriection(None)
  ,m_bIsAutoHide(false)
{
    //设备程序快捷键
    QxtGlobalShortcut* shortcut = new QxtGlobalShortcut(QKeySequence("Ctrl+B"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(show()));

    this->setFixedWidth(MAIN_WINDOW_WIDTH);
    this->setFixedHeight(MAIN_WINDOW_HEIGHT);

    //设置任务栏显示图标
    this->setWindowIcon(QIcon(QStringLiteral(":/resources/All_logo32-xp.ico")));

    m_login_widget          = NULL;
    m_system_tray_widget    = NULL;
    m_instant_msg_dialog    = NULL;
    m_mini_news_widget      = NULL;

    m_unread_msg_box_widget	= NULL;
    m_main_menu				= NULL;
    m_app_manager_widget	= NULL;
    m_msg_manager_widget	= NULL;
    m_file_share_widget		= NULL;
    m_collection_widget		= NULL;
    m_setting_pannel_widget	= NULL;
    m_about_dialog			= NULL;

//    m_weather_info_floating_widget = NULL;

    this->setupUi();
    this->retranslateUi();



//    if(!Baijuhua::Utils::SettingsUtils::load_plugin(m_network_info_plugin))
//    {
//        //如果无法加载插件
//        QMessageBox::information(this,"Error","Could not load the plugin");

//    }else{
//        QMessageBox::information(this,"Error","加载成功");
//    }


    connect(m_title_widget,SIGNAL(showMinimize()),this,SLOT(showMinimized()));//最小化
    connect(m_title_widget,SIGNAL(closeWidget()),qApp,SLOT(quit()));//退出程序
//    connect(m_title_widget,SIGNAL(closeWidget()),this,SLOT(close()));//退出程序

//    this->m_user_info_cover_widget->m_weather_lbl->installEventFilter(this);
    this->m_user_info_cover_widget->installEventFilter(this);

    m_nDesktopWidth = QApplication::desktop()->width();

    this->m_search_app_line_edit->installEventFilter(this);

}

MainWidget::~MainWidget()
{
    if(m_login_widget)
    {
        delete m_login_widget;
    }
    m_login_widget = NULL;

    if(m_system_tray_widget)
    {
        delete m_system_tray_widget;
    }
    m_system_tray_widget = NULL;

    if(m_instant_msg_dialog)
    {
        delete m_instant_msg_dialog;
    }
    m_instant_msg_dialog = NULL;

    if(m_unread_msg_box_widget)
    {
        delete m_unread_msg_box_widget;
    }
    m_unread_msg_box_widget = NULL;

    if(m_main_menu)
    {
        delete m_main_menu;
    }
    m_main_menu = NULL;

    if(m_app_manager_widget)
    {
        delete m_app_manager_widget;
    }
    m_app_manager_widget = NULL;

    if(m_msg_manager_widget)
    {
        delete m_msg_manager_widget;
    }
    m_msg_manager_widget = NULL;

    if(m_file_share_widget)
    {
        delete m_file_share_widget;
    }
    m_file_share_widget = NULL;

    if(m_collection_widget)
    {
        delete m_collection_widget;
    }
    m_collection_widget = NULL;

    if(m_setting_pannel_widget)
    {
        delete m_setting_pannel_widget;
    }
    m_setting_pannel_widget = NULL;

    if(m_about_dialog)
    {
        delete m_about_dialog;
    }
    m_about_dialog = NULL;


    if(m_mini_news_widget)
    {
        delete m_mini_news_widget;
    }
    m_mini_news_widget = NULL;

//    //天气预报
//    if(m_weather_info_floating_widget)
//    {
//        delete m_weather_info_floating_widget;
//    }
//    m_weather_info_floating_widget = NULL;

}

void MainWidget::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("MainWidget"));

    m_main_fame_v_layout = new QVBoxLayout(this);
    m_main_fame_v_layout->setObjectName(QStringLiteral("m_main_fame_v_layout"));
    m_main_fame_v_layout->setSpacing(0);
    m_main_fame_v_layout->setContentsMargins(0,0,0,0);

    init_top_widget();

    m_main_fame_v_layout->addWidget(m_top_widget,0,Qt::AlignTop);

    init_user_info_cover_widget();

    m_main_fame_v_layout->addWidget(m_user_info_widget,0,Qt::AlignTop);

    init_search_bar_widget();       

    m_main_fame_v_layout->addWidget(m_search_bar_widget,0,Qt::AlignTop);

    init_center_widget();

    //中间搜索栏弹出框与TAB的切换
    m_center_stacked_widget = new QStackedWidget();
    m_search_result_widget = new QWidget(m_center_stacked_widget);
//    m_search_result_widget->setStyleSheet(QStringLiteral("background-color:rgba(0,0,0,255);"));
    m_search_result_widget->setFixedHeight(470);

    m_center_stacked_widget->addWidget(m_search_result_widget);
    m_center_stacked_widget->addWidget(m_center_widget);

    m_center_stacked_widget->setCurrentWidget(m_center_widget);

    m_main_fame_v_layout->addWidget(m_center_stacked_widget,0,Qt::AlignTop);


//    m_main_fame_v_layout->addWidget(m_center_widget,0,Qt::AlignTop);

    init_bottom_widget();

    m_main_fame_v_layout->addWidget(m_bottom_widget,0,Qt::AlignTop);

}

void MainWidget::retranslateUi()
{
    m_search_app_line_edit->setPlaceholderText(QStringLiteral(u"搜索：联系人"));
}

void MainWidget::init_top_widget()
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

void MainWidget::init_user_info_cover_widget()
{
    m_user_info_widget = new QWidget();
    m_user_info_widget->setObjectName(QStringLiteral("m_user_info_widget"));
    m_user_info_widget->setFixedHeight(80);

    m_user_info_cover_widget = new UserInfoCoverWidget();
    m_user_info_cover_widget->setObjectName(QStringLiteral("m_user_info_cover_widget"));
    m_user_info_cover_widget->setFixedHeight(80);

    QHBoxLayout *m_user_info_h_layout = new QHBoxLayout(m_user_info_widget);
    m_user_info_h_layout->setSpacing(0);
    m_user_info_h_layout->setContentsMargins(0,0,0,0);

    m_user_info_h_layout->addWidget(m_user_info_cover_widget,0,Qt::AlignTop);

}

void MainWidget::init_search_bar_widget()
{
    m_search_bar_widget = new QWidget();
    m_search_bar_widget->setObjectName(QStringLiteral("m_search_bar_widget"));
    m_search_bar_widget->setFixedHeight(30);

    //标题栏右侧，搜索框
    QHBoxLayout *search_bar_h_layout = new QHBoxLayout(m_search_bar_widget);
    search_bar_h_layout->setObjectName(QStringLiteral("search_bar_h_layout"));
    search_bar_h_layout->setSpacing(0);
    search_bar_h_layout->setContentsMargins(0,0,0,0);

    m_search_app_line_edit = new AppSearchLineEdit();
    m_search_app_line_edit->setObjectName(QStringLiteral("m_search_app_line_edit"));
    m_search_app_line_edit->setMinimumWidth(220);
    m_search_app_line_edit->setFixedHeight(30);
    m_search_app_line_edit->setAutoFillBackground(true);
    m_search_app_line_edit->setContentsMargins(0,0,0,0);//设置搜索框与下载按钮间的间距
    search_bar_h_layout->addWidget(m_search_app_line_edit);
}

void MainWidget::init_center_widget()
{
    m_center_widget = new CenterWidget();
    m_center_widget->setObjectName(QStringLiteral("m_center_widget"));
    m_center_widget->setFixedHeight(470);

}

void MainWidget::init_bottom_widget()
{
    m_bottom_widget = new QWidget();
    m_bottom_widget->setObjectName(QStringLiteral("m_bottom_widget"));
    m_bottom_widget->setFixedHeight(60);

    m_bottom_function_widget  = new BottomFunctionWidget();
    m_bottom_function_widget->setObjectName(QStringLiteral("m_bottom_function_widget"));
    m_bottom_function_widget->setFixedHeight(60);

    //
    QVBoxLayout *m_bottom_v_layout = new QVBoxLayout(m_bottom_widget);
    m_bottom_v_layout->setObjectName(QStringLiteral("search_bar_h_layout"));
    m_bottom_v_layout->setSpacing(0);
    m_bottom_v_layout->setContentsMargins(0,0,0,0);

    m_bottom_v_layout->addWidget(m_bottom_function_widget,0,Qt::AlignBottom);
}



void MainWidget::onShowMainMenu()
{
    //设置主菜单出现的位置
    QPoint p = rect().bottomLeft();
    p.setX(p.x() + 12);
    p.setY(p.y() - 250);
    m_main_menu->exec(this->mapToGlobal(p));//更换成全局坐标
}

void MainWidget::onShowAppManagerWidget()
{
    if(m_app_manager_widget == NULL)
    {
        m_app_manager_widget = new AppManagerWidget();
    }

    m_app_manager_widget->show();
}

void MainWidget::onShowMsgManagerWidget()
{
    if(m_msg_manager_widget  == NULL)
    {
        m_msg_manager_widget = new MsgManagerWidget();
    }

    m_msg_manager_widget->show();
}

void MainWidget::onShowSettingPannelWidget()
{
    if(m_setting_pannel_widget  == NULL)
    {
        m_setting_pannel_widget = new SettingPannelWidget();
    }

    m_setting_pannel_widget->show();
}

void MainWidget::onShowUnreadMsgBoxWidget()
{
    if(m_unread_msg_box_widget  == NULL)
    {
        m_unread_msg_box_widget = new UnreadMsgBoxWidget();
    }

    m_unread_msg_box_widget->show();
}

void MainWidget::onShowFileShareWidget()
{
    if(m_file_share_widget  == NULL)
    {
        m_file_share_widget = new FileShareWidget();
    }

    m_file_share_widget->show();
}

void MainWidget::onShowCollectionWidget()
{
    if(m_collection_widget  == NULL)
    {
        m_collection_widget = new CollectionWidget();
    }

    m_collection_widget->show();
}

void MainWidget::onShowAboutDialog()
{
    if(m_about_dialog  == NULL){
        m_about_dialog = new AboutDialog();
    }
    //将窗体设置为模态的具体说明见http://www.360doc.com/content/15/0825/16/20016257_494656595.shtml
    m_about_dialog->setWindowModality(Qt::ApplicationModal);//将窗体设置为模态，方法1
    //m_login_dialog->setAttribute(Qt::WA_ShowModal,true);//方法2
    m_about_dialog->show();
}


void MainWidget::onShowMainWidget()
{
    this->showNormal();
    //让窗口成为顶层窗口和激活状态
    this->raise();
    this->activateWindow();
}


int MainWidget::onCreateLoginScreen()
{
    this->hide();

    if(this->m_login_widget == NULL)
    {
        m_login_widget = new LoginWidget();
    }

    return m_login_widget->exec();

}

void MainWidget::onCreateSystemScreen()
{
    this->show();//显示主窗体

    //----------托盘图标
    if (m_system_tray_widget == NULL)
    {
        m_system_tray_widget = new SystemTrayWidget(this);
//		connect(m_system_tray_widget,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
//			this,SLOT(doTrayIconActivated(QSystemTrayIcon::ActivationReason)));
        connect(m_system_tray_widget,SIGNAL(showMainWidget()),this,SLOT(onShowMainWidget()));
    }

    m_system_tray_widget->setVisible(true);//说明：http://blog.csdn.net/dbzhang800/article/details/6300021

    //-----------右下角消息对话框
    if(m_instant_msg_dialog == NULL)
    {
        m_instant_msg_dialog = new InstantMessageDialog(this);
        connect(this,SIGNAL(showInstantMessageDialog(QString,QString)),m_instant_msg_dialog,SLOT(onShowMessage(QString,QString)));
    }

    QString str_cur_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");//获取当前系统时间，以及设置显示格式
    emit showInstantMessageDialog(QStringLiteral(u"系统提示"),QStringLiteral(u"登录成功，操作系统为：登录时间为：") + str_cur_time);//登录验证成功，发出显示右下角即时消息对话框


    //-----------用户区消息盒子
    if(m_unread_msg_box_widget == NULL)
    {
        m_unread_msg_box_widget = new UnreadMsgBoxWidget();
        connect(m_user_info_cover_widget,SIGNAL(showUnreadMsgBoxWidget()),this,SLOT(onShowUnreadMsgBoxWidget()));
    }

    //-----------主菜单
    if(m_main_menu == NULL)
    {
        m_main_menu = new MainMenu();
        connect(m_bottom_function_widget,SIGNAL(showMainMenu()),this,SLOT(onShowMainMenu()));//显示主目录
        connect(m_main_menu,SIGNAL(showSettingPannelWidget()),this,SLOT(onShowSettingPannelWidget()));//显示设置对话框
    }

    //-----------应用管理器
    if(m_app_manager_widget == NULL)
    {
        m_app_manager_widget = new AppManagerWidget();
        connect(m_bottom_function_widget,SIGNAL(showAppManagerWidget()),this,SLOT(onShowAppManagerWidget()));
    }


    //-----------消息管理器
    if(m_msg_manager_widget == NULL)
    {
        m_msg_manager_widget = new MsgManagerWidget();
        connect(m_bottom_function_widget,SIGNAL(showMsgManagerWidget()),this,SLOT(onShowMsgManagerWidget()));
    }


    //-----------文件共享
    if(m_file_share_widget == NULL)
    {
        m_file_share_widget = new FileShareWidget();
        connect(m_bottom_function_widget,SIGNAL(showFileShareWidget()),this,SLOT(onShowFileShareWidget()));
    }


    //-----------收藏
    if(m_collection_widget == NULL)
    {
        m_collection_widget = new CollectionWidget();
        connect(m_bottom_function_widget,SIGNAL(showCollectionWidget()),this,SLOT(onShowCollectionWidget()));
    }

    //-----------设置中心
    if(m_setting_pannel_widget == NULL)
    {
        m_setting_pannel_widget = new SettingPannelWidget();
        connect(m_bottom_function_widget,SIGNAL(showSettingPannelWidget()),this,SLOT(onShowSettingPannelWidget()));
    }

    //-----------关于对话框
    if(m_about_dialog == NULL)
    {
        m_about_dialog = new AboutDialog();
        connect(m_main_menu,SIGNAL(showAboutDialog()),this,SLOT(onShowAboutDialog()));//显示关于对话框
    }


    //-----------迷你新闻弹出对话框 if(m_mini_news_widget == NULL)
//    {
//        m_mini_news_widget = new MiniNewsWidget();//如果加了this，则窗体显示不出来，不知道为什么
//    }
//    m_mini_news_widget->show();


}


//void MainWidget::onCreateWeatherInfoFloatingWidget()
//{
//    if(m_weather_info_floating_widget == NULL)
//    {
//        m_weather_info_floating_widget = new WeatherInfoFloatingWidget();//不能在构造函数中传递this对象，否则窗体不能正常显示
//        //QtWebEngine::initialize();
//    }
//    m_weather_info_floating_widget->hide();
//}

bool MainWidget::eventFilter(QObject *object, QEvent *event)
{
//    if (object == this->m_user_info_cover_widget->m_weather_lbl)
//    {
//        if (event->type() == QEvent::Enter)
//        {
//            if (m_weather_info_floating_widget == NULL)
//            {
//                onCreateWeatherInfoFloatingWidget();
//            }
//            QPoint pos = this->pos();
//            if (pos.x() > m_weather_info_floating_widget->width())
//            {
//                m_weather_info_floating_widget->move(pos.x() - m_weather_info_floating_widget->width(),pos.y());
//            }
//            else
//            {
//                m_weather_info_floating_widget->move(pos.x() + this->width(),pos.y());
//            }
//            m_weather_info_floating_widget->show();
//        }
//        else if (event->type() == QEvent::Leave)
//        {
//            if (m_weather_info_floating_widget)
//            {
//                m_weather_info_floating_widget->onHideWeatherInfoFloatingWidget();
//            }
//        }
//    }

    //搜索结果与TAB页切换
    if (object == this->m_search_app_line_edit)
    {
        if (event->type() == QEvent::FocusIn)
        {
            m_center_stacked_widget->setCurrentWidget(m_search_result_widget);
        }
        if (event->type() == QEvent::FocusOut)
        {
            m_center_stacked_widget->setCurrentWidget(m_center_widget);
        }

    }


    return DraggableWidget::eventFilter(object,event);
}

///
/// \brief 以下是主窗体靠边自动隐藏功能
///
///
void MainWidget::isAutoHide()
{
    QPoint pos = this->pos();

    m_bIsAutoHide = true;
    if (pos.x() < 2)
    {
        m_enDriection = Left;
    }
    else if (pos.y() < 2)
    {
        m_enDriection = Up;
    }
    else if (this->pos().x() + this->width() > m_nDesktopWidth - 2)
    {
        m_enDriection = Right;
    }
    else
    {
        m_enDriection = None;
        m_bIsAutoHide = false;
    }
}

void MainWidget::hideWidget()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(100);
    animation->setStartValue(QRect(this->pos(), this->size()));

    QRect rcEnd;
    if (m_enDriection & Up)
    {
        rcEnd = QRect(this->x(), -this->height() + 2, this->size().width(), this->rect().height());
    }
    else if (m_enDriection & Left)
    {
        rcEnd = QRect(-this->width() + 2, this->y(), this->size().width(), this->rect().height());
    }
    else if (m_enDriection & Right)
    {
        rcEnd = QRect(m_nDesktopWidth - 2, this->y(), this->size().width(), this->rect().height());
    }
    animation->setEndValue(rcEnd);
    animation->start();
}

void MainWidget::showWidget()
{
    QPoint pos = this->pos();

    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(100);
    animation->setStartValue(QRect(pos, this->size()));

    QRect rcEnd;
    if (m_enDriection & Up)
    {
        rcEnd = QRect(this->x(), 0-WINDOW_SHADOW_WIDTH, this->size().width(), this->rect().height());
    }
    else if (m_enDriection & Left)
    {
        rcEnd = QRect(0-WINDOW_SHADOW_WIDTH, this->y(), this->size().width(), this->rect().height());
    }
    else if (m_enDriection & Right)
    {
        rcEnd = QRect(m_nDesktopWidth - this->width()+WINDOW_SHADOW_WIDTH, this->y(), this->size().width(), this->rect().height());
    }
    animation->setEndValue(rcEnd);
    animation->start();
}

void MainWidget::leaveEvent(QEvent *event)
{
    isAutoHide();
    if (m_bIsAutoHide)
    {
        hideWidget();
    }
    DraggableWidget::leaveEvent(event);
}

void MainWidget::enterEvent(QEvent *event)
{
    if (m_bIsAutoHide)
    {
        showWidget();
    }
    DraggableWidget::enterEvent(event);
}

///
/// \brief 以上是主窗体靠边自动隐藏功能
///
///
///


void MainWidget::set_auto_run_by_regedit(bool is_auto_run)
{
    QString application_name = QApplication::applicationName();
    QSettings *settings = new QSettings(REG_RUN, QSettings::NativeFormat);
    if(is_auto_run)
    {
        QString application_path = QApplication::applicationFilePath();
        settings->setValue(application_name, application_path.replace("/", "\\"));
    }
    else
    {
        settings->remove(application_name);
    }
    delete settings;
}
