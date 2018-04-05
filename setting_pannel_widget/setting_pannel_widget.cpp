#include "setting_pannel_widget.h"

SettingPannelWidget::SettingPannelWidget(QWidget *parent) : DraggableWidget(parent)
{
    this->setFixedSize(SETTING_PANNEL_WIDTH,SETTING_PANNEL_HEIGHT);

    this->setupUi();
    this->retranslateUi();

    QPixmap pixmap(QStringLiteral(":/resources/logo-QQ.png"));
    this->m_logo_lbl->setPixmap(pixmap);
    this->m_logo_lbl->show();

    //
    connect(m_min_btn,SIGNAL(clicked(bool)),this,SLOT(showMinimized()));//最小化窗体
    connect(m_close_btn,SIGNAL(clicked(bool)),this,SLOT(close()));//关闭窗体
}


SettingPannelWidget::~SettingPannelWidget()
{

}

void SettingPannelWidget::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("SettingPannelWidget"));

    m_main_v_layout = new QVBoxLayout(this);
    m_main_v_layout->setObjectName(QStringLiteral("m_main_v_layout"));
    m_main_v_layout->setContentsMargins(0,0,0,0);
    m_main_v_layout->setSpacing(0);

    init_title_widget();

    m_main_v_layout->addWidget(m_title_widget,0,Qt::AlignTop);

    init_tab_widget();

    m_main_v_layout->addWidget(m_tab_widget,0,Qt::AlignTop);
    m_main_v_layout->addStretch(0);

}

void SettingPannelWidget::init_title_widget()
{
    m_title_widget = new QWidget(this);
    m_title_widget->setObjectName(QStringLiteral("m_title_widget"));
    m_title_widget->setFixedHeight(SETTING_PANNEL_TITLE_HEIGHT);

    m_title_h_layout = new QHBoxLayout(m_title_widget);
    m_title_h_layout->setSpacing(0);
    m_title_h_layout->setObjectName(QStringLiteral("m_title_h_layout"));
    m_title_h_layout->setContentsMargins(MAIN_PANNEL_LEFT_MARGIN, 0, 0, 0);

    m_logo_lbl = new QLabel();
    m_logo_lbl->setObjectName(QStringLiteral("m_logo_lbl"));

    m_title_h_layout->addWidget(m_logo_lbl);

    m_app_name_lbl = new QLabel();
    m_app_name_lbl->setObjectName(QStringLiteral("m_app_name_lbl"));

    m_title_h_layout->addWidget(m_app_name_lbl);

    m_title_h_layout->addStretch(0);


    //最小化按钮
    m_min_btn = new QPushButton();
    m_min_btn->setObjectName(QStringLiteral("m_min_btn"));

    m_title_h_layout->addWidget(m_min_btn,0,Qt::AlignTop);

    //关闭按钮
    m_close_btn = new QPushButton();
    m_close_btn->setObjectName(QStringLiteral("m_close_btn"));

    m_title_h_layout->addWidget(m_close_btn,0,Qt::AlignTop);

}

//初始化TabWidget
void SettingPannelWidget::init_tab_widget()
{
    m_tab_widget = new QWidget(this);
    m_tab_widget->setObjectName(QStringLiteral("m_tab_widget"));

    //Tab Widget整体垂直布局
    m_tab_widget_v_layout = new QVBoxLayout(m_tab_widget);
    m_tab_widget_v_layout->setObjectName(QStringLiteral("m_tab_widget_v_layout"));
    m_tab_widget_v_layout->setSpacing(0);
    m_tab_widget_v_layout->setContentsMargins(0,0,0,0);

    init_tab_bar_widget();//初始化TabBar

    m_tab_widget_v_layout->addWidget(m_tab_bar_wdiget,0,Qt::AlignTop);
    m_tab_widget_v_layout->addStretch(0);
    m_tab_widget_v_layout->setStretchFactor(m_tab_bar_wdiget,1);

    //tab_page页
    m_stacked_widget = new QStackedWidget();//tab_page容器
    m_stacked_widget->setObjectName(QStringLiteral("m_stacked_widget"));

    m_tab_widget_v_layout->addWidget(m_stacked_widget,0,Qt::AlignTop);

    init_tab_page_widget();//初始化TabPage

    connect(m_tab_button_group,SIGNAL(buttonClicked(int)),m_stacked_widget,SLOT(setCurrentIndex(int)));

}


void SettingPannelWidget::init_tab_bar_widget()
{
    //tab_bar标签项
    m_tab_bar_wdiget = new QWidget();
    m_tab_bar_wdiget->setObjectName(QStringLiteral("m_tab_bar_wdiget"));
    m_tab_bar_wdiget->setContentsMargins(0,0,0,0);
    m_tab_bar_wdiget->setFixedHeight(44);

    m_button_h_layout = new QHBoxLayout(m_tab_bar_wdiget);
    m_button_h_layout->setObjectName(QStringLiteral("m_button_h_layout"));
    m_button_h_layout->setSpacing(20);
    m_button_h_layout->setContentsMargins(10,0,0,0);
    //m_button_h_layout->addStretch(0);

    m_tab_button_group = new QButtonGroup(m_tab_bar_wdiget);
    m_tab_button_group->setExclusive(true);//设置排它性

    m_basic_setting_tbtn = new QToolButton();
    m_basic_setting_tbtn->setObjectName(QStringLiteral("m_basic_setting_tbtn"));
    m_basic_setting_tbtn->setCheckable(true);
    m_basic_setting_tbtn->setFixedSize(90,30);

    m_button_h_layout->addWidget(m_basic_setting_tbtn,0,Qt::AlignVCenter|Qt::AlignLeft);
    m_tab_button_group->addButton(m_basic_setting_tbtn,0);
    m_basic_setting_tbtn->setChecked(true);//设置第一个按钮默认为checked;

    m_security_setting_tbtn = new QToolButton();
    m_security_setting_tbtn->setObjectName(QStringLiteral("m_security_setting_tbtn"));
    m_security_setting_tbtn->setCheckable(true);
    m_security_setting_tbtn->setFixedSize(90,30);

    m_button_h_layout->addWidget(m_security_setting_tbtn,0,Qt::AlignVCenter|Qt::AlignLeft);
    m_tab_button_group->addButton(m_security_setting_tbtn,1);

    m_secrecy_setting_tbtn = new QToolButton();
    m_secrecy_setting_tbtn->setObjectName(QStringLiteral("m_secrecy_setting_tbtn"));
    m_secrecy_setting_tbtn->setCheckable(true);
    m_secrecy_setting_tbtn->setFixedSize(90,30);


    m_button_h_layout->addWidget(m_secrecy_setting_tbtn,0,Qt::AlignVCenter|Qt::AlignLeft);
    m_tab_button_group->addButton(m_secrecy_setting_tbtn,2);

    m_button_h_layout->addStretch(0);

}


void SettingPannelWidget::init_tab_page_widget()
{
    init_basic_setting_tab();
    init_security_setting_tab();
    init_secrecy_setting_tab();

    //将各Tab page添加至stacked_widget
    m_stacked_widget->addWidget(m_basic_setting_tab);
    m_stacked_widget->addWidget(m_security_setting_tab);
    m_stacked_widget->addWidget(m_secrecy_setting_tab);
}


void SettingPannelWidget::init_basic_setting_tab()
{

    m_basic_setting_tab = new QWidget();
    m_basic_setting_tab->setObjectName(QStringLiteral("m_basic_setting_tab"));
    m_basic_setting_tab->setContentsMargins(0,0,0,0);
    m_basic_setting_tab->setFixedHeight(this->height()- m_title_widget->height()- m_tab_bar_wdiget->height());
    m_basic_setting_tab->setFixedWidth(this->width());

    QVBoxLayout *m_basic_setting_v_layout = new QVBoxLayout(m_basic_setting_tab);
    m_basic_setting_v_layout->setSpacing(0);
    m_basic_setting_v_layout->setContentsMargins(0,0,0,0);


    m_basic_setting_tab_page_widget = new BasicSettingTabPageWidget();
    m_basic_setting_tab_page_widget->setObjectName(QStringLiteral("m_basic_setting_tab_page_widget"));
    m_basic_setting_tab_page_widget->setFixedHeight(m_basic_setting_tab->height());
    m_basic_setting_tab_page_widget->setFixedWidth(m_basic_setting_tab->width());
    m_basic_setting_v_layout->addWidget(m_basic_setting_tab_page_widget,0,Qt::AlignTop);




}


void SettingPannelWidget::init_security_setting_tab()
{
    m_security_setting_tab = new QWidget();
    m_security_setting_tab->setObjectName(QStringLiteral("m_security_setting_tab"));
    m_security_setting_tab->setContentsMargins(0,0,0,0);
    m_security_setting_tab->setFixedHeight(this->height()- m_title_widget->height()- m_tab_bar_wdiget->height());
    m_security_setting_tab->setFixedWidth(this->width());

    QVBoxLayout *m_security_setting_v_layout = new QVBoxLayout(m_security_setting_tab);
    m_security_setting_v_layout->setSpacing(0);
    m_security_setting_v_layout->setContentsMargins(0,0,0,0);


    m_security_setting_tab_page_widget = new SecuritySettingTabPageWidget();
    m_security_setting_tab_page_widget->setObjectName(QStringLiteral("m_security_setting_tab_page_widget"));
    m_security_setting_tab_page_widget->setFixedHeight(m_security_setting_tab->height());
    m_security_setting_tab_page_widget->setFixedWidth(m_security_setting_tab->width());
    m_security_setting_v_layout->addWidget(m_security_setting_tab_page_widget,0,Qt::AlignTop);
}


void SettingPannelWidget::init_secrecy_setting_tab()
{
    m_secrecy_setting_tab = new QWidget();
    m_secrecy_setting_tab->setObjectName(QStringLiteral("m_secrecy_setting_tab"));
    m_secrecy_setting_tab->setContentsMargins(0,0,0,0);
    m_secrecy_setting_tab->setFixedHeight(this->height()- m_title_widget->height()- m_tab_bar_wdiget->height());
    m_secrecy_setting_tab->setFixedWidth(this->width());

    QVBoxLayout *m_secrecy_setting_v_layout = new QVBoxLayout(m_secrecy_setting_tab);
    m_secrecy_setting_v_layout->setSpacing(0);
    m_secrecy_setting_v_layout->setContentsMargins(0,0,0,0);


    m_secrecy_setting_tab_page_widget = new SecrecySettingTabPageWidget();
    m_secrecy_setting_tab_page_widget->setObjectName(QStringLiteral("m_secrecy_setting_tab_page_widget"));
    m_secrecy_setting_tab_page_widget->setFixedHeight(m_secrecy_setting_tab->height());
    m_secrecy_setting_tab_page_widget->setFixedWidth(m_secrecy_setting_tab->width());
    m_secrecy_setting_v_layout->addWidget(m_secrecy_setting_tab_page_widget,0,Qt::AlignTop);

}


void SettingPannelWidget::retranslateUi()
{
    //m_app_name_lbl->setText(QStringLiteral("软件名称"));
    m_min_btn->setText(QString());
    m_close_btn->setText(QString());

    this->m_basic_setting_tbtn->setText(QStringLiteral("基本设置"));
    this->m_security_setting_tbtn->setText(QStringLiteral("安全设置"));
    this->m_secrecy_setting_tbtn->setText(QStringLiteral("权限设置"));
}


void SettingPannelWidget::mousePressEvent(QMouseEvent *event)
{
    DraggableWidget::mousePressEvent(event);
}
