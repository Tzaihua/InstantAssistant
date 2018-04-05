#include "center_widget.h"

CenterWidget::CenterWidget(QWidget *parent) : QWidget(parent)
{
    setupUi();
    retranslateUi();


}


void CenterWidget::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("MainTabWidget"));

    init_tab_widget();

}

void CenterWidget::retranslateUi()
{
    //临时设置tabpage面板颜色，用于区分各个tabpage
    m_contact_tab->setStyleSheet(QStringLiteral("QWidget{background-color:white;}"));
    m_group_tab->setStyleSheet(QStringLiteral("QWidget{background-color:yellow;}"));
    m_app_tab->setStyleSheet(QStringLiteral("QWidget{background-color:gray;}"));
    m_mobile_tab->setStyleSheet(QStringLiteral("QWidget{background-color:red;}"));
    m_history_tab->setStyleSheet(QStringLiteral("QWidget{background-color:blue;}"));

    //tab button鼠标悬停提示
    m_contact_tbtn->setToolTip(QStringLiteral("联系人"));
    m_group_tbtn->setToolTip(QStringLiteral("群聊"));
    m_app_tbtn->setToolTip(QStringLiteral("应用"));
    m_mobile_tbtn->setToolTip(QStringLiteral("手机"));
    m_history_tbtn->setToolTip(QStringLiteral("会话"));

}


void CenterWidget::init_tab_widget()
{

    //主布局
    m_main_v_layout = new QVBoxLayout(this);
    m_main_v_layout->setObjectName(QStringLiteral("m_main_v_layout"));
    m_main_v_layout->setSpacing(0);
    m_main_v_layout->setContentsMargins(0,0,0,0);

    init_tab_bar_widget();//初始化TabBar

    m_main_v_layout->addWidget(m_tab_bar_wdiget,0,Qt::AlignTop);
    m_main_v_layout->addStretch(0);
    m_main_v_layout->setStretchFactor(m_tab_bar_wdiget,1);

    //tab_page页
    m_stacked_widget = new QStackedWidget(this);//tab_page容器
    m_stacked_widget->setObjectName(QStringLiteral("m_stacked_widget"));

    m_main_v_layout->addWidget(m_stacked_widget,0,Qt::AlignTop);

    init_tab_page_widget();//初始化TabPage

    connect(m_tab_button_group,SIGNAL(buttonClicked(int)),m_stacked_widget,SLOT(setCurrentIndex(int)));

}

void CenterWidget::init_tab_page_widget()
{
    init_contact_tab();
    init_group_tab();
    init_app_tab();
    init_mobile_tab();
    init_history_tab();

    m_stacked_widget->addWidget(m_contact_tab);
    m_stacked_widget->addWidget(m_group_tab);
    m_stacked_widget->addWidget(m_app_tab);
    //m_stacked_widget->addWidget(m_mobile_tab);
    m_stacked_widget->addWidget(m_p_mobile_tab_web_view);
    m_stacked_widget->addWidget(m_history_tab);

}

void CenterWidget::init_tab_bar_widget()
{
    //tab_bar标签项
    m_tab_bar_wdiget = new QWidget();
    m_tab_bar_wdiget->setObjectName(QStringLiteral("m_tab_bar_wdiget"));
    m_tab_bar_wdiget->setContentsMargins(0,0,0,0);
    m_tab_bar_wdiget->setFixedHeight(36);

    m_button_h_layout = new QHBoxLayout(m_tab_bar_wdiget);
    m_button_h_layout->setObjectName(QStringLiteral("m_button_h_layout"));
    m_button_h_layout->setSpacing(0);
    m_button_h_layout->setContentsMargins(0,0,0,0);
    //m_button_h_layout->addStretch(0);

    m_tab_button_group = new QButtonGroup(m_tab_bar_wdiget);
    m_tab_button_group->setExclusive(true);//设置排它性

    m_contact_tbtn = new ToolButton();
    m_contact_tbtn->setObjectName(QStringLiteral("m_contact_tbtn"));
    m_contact_tbtn->set_normal_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/icon_contacts_normal.png")));
    m_contact_tbtn->set_active_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/icon_contacts_hover.png")));
    m_contact_tbtn->set_selected_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/icon_contacts_selected.png")));

    m_button_h_layout->addWidget(m_contact_tbtn,0,Qt::AlignVCenter);
    m_tab_button_group->addButton(m_contact_tbtn,0);
    m_contact_tbtn->setChecked(true);//设置第一个按钮默认为checked;

    m_group_tbtn = new ToolButton();
    m_group_tbtn->setObjectName(QStringLiteral("m_group_tbtn"));
    m_group_tbtn->set_normal_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/icon_group_normal.png")));
    m_group_tbtn->set_active_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/icon_group_hover.png")));
    m_group_tbtn->set_selected_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/icon_group_selected.png")));

    m_button_h_layout->addWidget(m_group_tbtn,0,Qt::AlignVCenter);
    m_tab_button_group->addButton(m_group_tbtn,1);

    m_app_tbtn = new ToolButton();
    m_app_tbtn->setObjectName(QStringLiteral("m_app_tbtn"));
    m_app_tbtn->set_normal_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/icon_appbox_normal.png")));
    m_app_tbtn->set_active_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/icon_appbox_hover.png")));
    m_app_tbtn->set_selected_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/icon_appbox_selected.png")));

    m_button_h_layout->addWidget(m_app_tbtn,0,Qt::AlignVCenter);
    m_tab_button_group->addButton(m_app_tbtn,2);

    m_mobile_tbtn = new ToolButton();
    m_mobile_tbtn->setObjectName(QStringLiteral("m_mobile_tbtn"));
    m_mobile_tbtn->set_normal_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/mobileqq_offline2x.png")));
    m_mobile_tbtn->set_active_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/mobileicon_hover2x.png")));
    m_mobile_tbtn->set_selected_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/mobileqq_online2x.png")));

    m_button_h_layout->addWidget(m_mobile_tbtn,0,Qt::AlignVCenter);
    m_tab_button_group->addButton(m_mobile_tbtn,3);

    m_history_tbtn = new ToolButton();
    m_history_tbtn->setObjectName(QStringLiteral("m_history_tbtn"));
    m_history_tbtn->set_normal_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/icon_last_normal.png")));
    m_history_tbtn->set_active_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/icon_last_hover.png")));
    m_history_tbtn->set_selected_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/icon_last_selected.png")));

    m_button_h_layout->addWidget(m_history_tbtn,0,Qt::AlignVCenter);
    m_tab_button_group->addButton(m_history_tbtn,4);

}


void CenterWidget::init_contact_tab()
{
    m_contact_tab = new QWidget(m_stacked_widget);
    m_contact_tab->setObjectName(QStringLiteral("m_contact_tab"));
    m_contact_tab->setContentsMargins(0,0,0,0);
    m_contact_tab->setFixedHeight(this->height()-m_tab_bar_wdiget->height());


    m_contact_v_layout = new QVBoxLayout(m_contact_tab);
    m_contact_v_layout->setObjectName(QStringLiteral("m_contact_v_layout"));
    m_contact_v_layout->setContentsMargins(0,0,0,0);

    m_contact_list_widget = new QListWidget();
    m_contact_list_widget->setObjectName(QStringLiteral("m_contact_list_widget"));
    m_contact_list_widget->setFixedHeight(m_contact_tab->height());

    m_contact_v_layout->addWidget(m_contact_list_widget,0,Qt::AlignTop);
    m_contact_v_layout->addStretch(0);




}

void CenterWidget::init_group_tab()
{
    m_group_tab = new QWidget();
    m_group_tab->setObjectName(QStringLiteral("m_group_tab"));
    m_group_tab->setContentsMargins(0,0,0,0);
    m_group_tab->setFixedHeight(this->height()-m_tab_bar_wdiget->height());


    m_group_v_layout = new QVBoxLayout(m_group_tab);
    m_group_v_layout->setObjectName(QStringLiteral("m_group_v_layout"));
    m_group_v_layout->setContentsMargins(0,0,0,0);


}

void CenterWidget::init_app_tab()
{
    m_app_tab = new QWidget();
    m_app_tab->setObjectName(QStringLiteral("m_app_tab"));
    m_app_tab->setContentsMargins(0,0,0,0);
    m_app_tab->setFixedHeight(this->height()-m_tab_bar_wdiget->height());


    m_app_v_layout = new QVBoxLayout(m_app_tab);
    m_app_v_layout->setObjectName(QStringLiteral("m_app_v_layout"));
    m_app_v_layout->setContentsMargins(0,0,0,0);


}

void CenterWidget::init_mobile_tab()
{
    m_mobile_tab = new QWidget();
    m_mobile_tab->setObjectName(QStringLiteral("m_mobile_tab"));
    m_mobile_tab->setContentsMargins(0,0,0,0);
    m_mobile_tab->setFixedHeight(this->height()-m_tab_bar_wdiget->height());


    m_p_mobile_tab_web_view = new QWebEngineView();
    m_p_mobile_tab_web_view->setContentsMargins(0,0,0,0);
    m_p_mobile_tab_web_view->setFixedHeight(this->height()-m_tab_bar_wdiget->height());
    QWebEngineProfile::defaultProfile()->setHttpUserAgent(QStringLiteral("Mozilla/5.0 (Linux; Android 5.1.1; vivo X7 Build/LMY47V; wv) AppleWebKit/537.36 (KHTML, like Gecko) Version/4.0 Chrome/48.0.2564.116 Mobile "));
    m_mobile_v_layout = new QVBoxLayout(m_p_mobile_tab_web_view);
    //m_mobile_v_layout = new QVBoxLayout(m_mobile_tab);
    m_mobile_v_layout->setObjectName(QStringLiteral("m_mobile_v_layout"));
    m_mobile_v_layout->setContentsMargins(0,0,0,0);


    m_p_mobile_tab_web_view->setUrl(QUrl("http://www.baidu.com"));
    m_p_mobile_tab_web_view->settings()->setAttribute(QWebEngineSettings::PluginsEnabled,true);
    m_p_mobile_tab_web_view->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled,true);//支持JS

}

void CenterWidget::init_history_tab()
{
    m_history_tab = new QWidget();
    m_history_tab->setObjectName(QStringLiteral("m_history_tab"));
    m_history_tab->setContentsMargins(0,0,0,0);
    m_history_tab->setFixedHeight(this->height()-m_tab_bar_wdiget->height());


    m_history_v_layout = new QVBoxLayout(m_history_tab);
    m_history_v_layout->setObjectName(QStringLiteral("m_history_v_layout"));
    m_history_v_layout->setContentsMargins(0,0,0,0);

}


