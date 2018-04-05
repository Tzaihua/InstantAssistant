#include "msg_manager_widget.h"

MsgManagerWidget::MsgManagerWidget(QWidget *parent) : DraggableWidget(parent)
{
    this->setFixedSize(SETTING_PANNEL_WIDTH,SETTING_PANNEL_HEIGHT);
    this->setupUi();
    this->retranslateUi();

    connect(m_dialog_title_widget,SIGNAL(showMinimize()),this,SLOT(showMinimized()));//最小化
    connect(m_dialog_title_widget,SIGNAL(closeWidget()),this,SLOT(close()));//关闭窗体
}

MsgManagerWidget::~MsgManagerWidget()
{

}

void MsgManagerWidget::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("MsgManagerWidget"));

    m_main_v_layout = new QVBoxLayout(this);
    m_main_v_layout->setObjectName(QStringLiteral("m_main_v_layout"));
    m_main_v_layout->setContentsMargins(0,0,0,0);
    m_main_v_layout->setSpacing(0);

    m_dialog_title_widget = new DialogTitleWidget();
    m_dialog_title_widget->setObjectName(QStringLiteral("m_dialog_title_widget"));


    m_main_v_layout->addWidget(m_dialog_title_widget,0,Qt::AlignTop);

    init_tab_widget();//初始化tab widget部件

    m_main_v_layout->addWidget(m_tab_widget,0,Qt::AlignTop);
    m_main_v_layout->addStretch(0);


}


void MsgManagerWidget::init_tab_widget()
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

void MsgManagerWidget::init_tab_bar_widget()
{
    //tab_bar标签项
    m_tab_bar_wdiget = new QWidget();
    m_tab_bar_wdiget->setObjectName(QStringLiteral("m_tab_bar_wdiget"));
    m_tab_bar_wdiget->setContentsMargins(0,0,0,0);
    m_tab_bar_wdiget->setFixedHeight(44);

    m_button_h_layout = new QHBoxLayout(m_tab_bar_wdiget);
    m_button_h_layout->setObjectName(QStringLiteral("m_button_h_layout"));
    m_button_h_layout->setSpacing(5);
    m_button_h_layout->setContentsMargins(10,0,0,0);
    //m_button_h_layout->addStretch(0);

    m_tab_button_group = new QButtonGroup(m_tab_bar_wdiget);
    m_tab_button_group->setExclusive(true);//设置排它性

    m_contact_msg_tbtn = new QToolButton();
    m_contact_msg_tbtn->setObjectName(QStringLiteral("m_contact_msg_tbtn"));
    m_contact_msg_tbtn->setCheckable(true);
    m_contact_msg_tbtn->setMinimumSize(70,30);
//    m_contact_msg_tbtn->setFixedSize(90,30);

    m_button_h_layout->addWidget(m_contact_msg_tbtn,0,Qt::AlignVCenter|Qt::AlignLeft);
    m_tab_button_group->addButton(m_contact_msg_tbtn,0);
    m_contact_msg_tbtn->setChecked(true);//设置第一个按钮默认为checked;

    m_group_msg_tbtn = new QToolButton();
    m_group_msg_tbtn->setObjectName(QStringLiteral("m_group_msg_tbtn"));
    m_group_msg_tbtn->setCheckable(true);
    m_group_msg_tbtn->setMinimumSize(70,30);
//    m_group_msg_tbtn->setFixedSize(90,30);

    m_button_h_layout->addWidget(m_group_msg_tbtn,0,Qt::AlignVCenter|Qt::AlignLeft);
    m_tab_button_group->addButton(m_group_msg_tbtn,1);

    m_plugins_msg_tbtn = new QToolButton();
    m_plugins_msg_tbtn->setObjectName(QStringLiteral("m_plugins_msg_tbtn"));
    m_plugins_msg_tbtn->setCheckable(true);
    m_plugins_msg_tbtn->setMinimumSize(70,30);
//    m_plugins_msg_tbtn->setFixedSize(90,30);


    m_button_h_layout->addWidget(m_plugins_msg_tbtn,0,Qt::AlignVCenter|Qt::AlignLeft);
    m_tab_button_group->addButton(m_plugins_msg_tbtn,2);

    m_sys_msg_tbtn = new QToolButton();
    m_sys_msg_tbtn->setObjectName(QStringLiteral("m_sys_msg_tbtn"));
    m_sys_msg_tbtn->setCheckable(true);
    m_sys_msg_tbtn->setMinimumSize(70,30);
//    m_sys_msg_tbtn->setFixedSize(90,30);


    m_button_h_layout->addWidget(m_sys_msg_tbtn,0,Qt::AlignVCenter|Qt::AlignLeft);
    m_tab_button_group->addButton(m_sys_msg_tbtn,3);

    m_mobile_msg_tbtn = new QToolButton();
    m_mobile_msg_tbtn->setObjectName(QStringLiteral("m_mobile_msg_tbtn"));
    m_mobile_msg_tbtn->setCheckable(true);
    m_mobile_msg_tbtn->setMinimumSize(70,30);
//    m_mobile_msg_tbtn->setFixedSize(90,30);


    m_button_h_layout->addWidget(m_mobile_msg_tbtn,0,Qt::AlignVCenter|Qt::AlignLeft);
    m_tab_button_group->addButton(m_mobile_msg_tbtn,4);

    m_button_h_layout->addStretch(0);
}

void MsgManagerWidget::init_tab_page_widget()
{

}

void MsgManagerWidget::retranslateUi()
{
    m_contact_msg_tbtn->setText(QStringLiteral("联系人"));//联系人消息
    m_group_msg_tbtn->setText(QStringLiteral("群"));//群消息
    m_plugins_msg_tbtn->setText(QStringLiteral("插件消息"));//插件消息
    m_sys_msg_tbtn->setText(QStringLiteral("系统消息"));//系统消息
    m_mobile_msg_tbtn->setText(QStringLiteral("手机消息"));//手机消息
}

void MsgManagerWidget::onShowMinimize()
{
}

void MsgManagerWidget::onCloseWidget()
{
}
