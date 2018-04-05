#include "basic_setting_tab_page_widget.h"

BasicSettingTabPageWidget::BasicSettingTabPageWidget(QWidget *parent) : QWidget(parent)
{
    this->setupUi();
    this->retranslateUi();

    //如果Item不为空，则显示第一条
    if(m_left_category_list_widget->count() > 0){
        m_left_category_list_widget->setCurrentRow(0);
    }

    connect(m_left_category_list_widget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onListWidgetItemClicked(QListWidgetItem*)));
    connect(m_right_setting_scroll_area->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(onScrollAreaValueChanged(int)));

    m_ls_auto_start_chk->installEventFilter(this);
    m_ls_open_login_prompt_chk->installEventFilter(this);
    m_ls_subscribe_to_daily_info_chk->installEventFilter(this);
    m_mps_display_at_the_front_chk->installEventFilter(this);
    m_mps_auto_hide_when_docked_on_desktop_edge_chk->installEventFilter(this);
    m_mps_show_icon_in_taskbar_notification_area_chk->installEventFilter(this);
    m_mps_quit_chk->installEventFilter(this);
    m_mps_hide_to_taskbar_chk->installEventFilter(this);
    m_ms_session_msg_chk->installEventFilter(this);
    m_ms_android_device_conn_chk->installEventFilter(this);
    m_aus_auto_update_rbtn->installEventFilter(this);
    m_aus_manual_update_rbtn->installEventFilter(this);



}

BasicSettingTabPageWidget::~BasicSettingTabPageWidget()
{

}

void BasicSettingTabPageWidget::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("BasicSettingTabPageWidget"));

    this->setFixedWidth(SETTING_PANNEL_WIDTH);//设置为设置中心的宽度

    m_main_h_layout = new QHBoxLayout(this);
    m_main_h_layout->setObjectName(QStringLiteral("m_main_h_layout"));
    m_main_h_layout->setContentsMargins(0, 0, 0, 0);
    m_main_h_layout->setSpacing(0);

    m_left_category_list_widget = new QListWidget(this);
    m_left_category_list_widget->setObjectName(QStringLiteral("m_left_category_list_widget"));
    m_left_category_list_widget->setFixedWidth(SETTING_PANNEL_LEFT_LIST_WIDGET_WIDTH);//130
//    m_left_category_list_widget->setFixedHeight(this->height());//可能有问题
    m_left_category_list_widget->setFocusPolicy(Qt::NoFocus);


    m_main_h_layout->addWidget(m_left_category_list_widget);

    m_right_setting_scroll_area = new QScrollArea(this);
    m_right_setting_scroll_area->setObjectName(QStringLiteral("m_right_setting_scroll_area"));
    m_right_setting_scroll_area->setStyleSheet("QScrollArea{background-color:rgba(255,255,255,255);}"
                                            "QScrollBar::vertical{background:#9e9e9e;border:-5px solid grey;margin:-2px 0px 0px 0px;width:8px;}"
                                            "QScrollBar::horizontal{background:#9e9e9e;border:0px solid #126691;height:10px;}"
                                            "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background:#D3D3D3;}"
                                            );
    m_right_setting_scroll_area->setFrameShape(QFrame::NoFrame);
    m_right_setting_scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_right_setting_scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_right_setting_scroll_area->setFocusPolicy(Qt::NoFocus);
    m_right_setting_scroll_area->setFixedWidth(this->width() - m_left_category_list_widget->width() - 10);//这儿之所以要再减10，是因为，有10PX的边拿去阴影边框去了



    m_scroll_contents_widget = new QWidget();
    m_scroll_contents_widget->setObjectName(QStringLiteral("m_scroll_contents_widget"));
    m_scroll_contents_widget->setStyleSheet(QStringLiteral("background:rgba(255,255,255,255);"));

    m_right_setting_scroll_area->takeWidget();
    m_right_setting_scroll_area->setWidget(m_scroll_contents_widget);
    m_right_setting_scroll_area->setWidgetResizable(false);//只有把这儿设置为false才能实现点选，同时要增大m_scroll_contents_widget的尺寸

    init_login_setting_widget();
    m_scroll_contents_widget->resize(this->width(),400);

    init_main_pannel_setting_widget();
    m_scroll_contents_widget->resize(this->width(),800);

    init_remind_settting_widget();
    m_scroll_contents_widget->resize(this->width(),1200);

    init_app_update_setting_widget();
    m_scroll_contents_widget->resize(this->width(),1600);

    m_main_h_layout->addWidget(m_right_setting_scroll_area);
    m_main_h_layout->addStretch(0);


    QMetaObject::connectSlotsByName(this);

}


void BasicSettingTabPageWidget::init_login_setting_widget()
{
    //登录设置页
    m_login_setting_widget = new QWidget(m_scroll_contents_widget);
    m_login_setting_widget->setObjectName(QStringLiteral("m_login_setting_widget"));
    m_login_setting_widget->setStyleSheet(QStringLiteral("background-color:rgba(255,255,0,255);"));
    m_login_setting_widget->setGeometry(QRect(0, 0, 600, 180));
    m_login_setting_widget->show();

    //登录页水平布局，总体布局
    m_ls_main_h_layout = new QHBoxLayout(m_login_setting_widget);
    m_ls_main_h_layout->setContentsMargins(SETTING_PANNEL_RIGHT_SCROLL_AREA_LEFT_MARGIN, SETTING_PANNEL_RIGHT_SCROLL_AREA_TOP_MARGIN, 0, 0);


    //登录页左侧的类型项名称--登录
    m_ls_category_lbl = new QLabel();
    m_ls_category_lbl->setObjectName(QStringLiteral("m_ls_category_lbl"));
    m_ls_category_lbl->setFixedWidth(SETTING_PANNEL_RIGHT_SCROLL_AREA_CATEGORY_LABEL_WIDTH);
    m_ls_category_lbl->show();

    //登录页右侧具体设置的垂直布局，所有设置均在此布局下面
    m_ls_main_h_layout->addWidget(m_ls_category_lbl,0,Qt::AlignLeft|Qt::AlignTop);

    m_ls_setting_v_layout = new QVBoxLayout();
    m_ls_setting_v_layout->setSpacing(SETTING_PANNEL_RIGHT_SCROLL_AREA_SPACE);

    //自动启动
    m_ls_auto_start_chk = new QCheckBox(m_login_setting_widget);
    m_ls_auto_start_chk->setObjectName(QStringLiteral("m_ls_auto_start_chk"));
    m_ls_auto_start_chk->show();

    m_ls_setting_v_layout->addWidget(m_ls_auto_start_chk,0,Qt::AlignLeft|Qt::AlignTop);

    //打开登录提示
    m_ls_open_login_prompt_chk = new QCheckBox(m_login_setting_widget);
    m_ls_open_login_prompt_chk->setObjectName(QStringLiteral("m_ls_open_login_prompt_chk"));
    m_ls_open_login_prompt_chk->show();

    m_ls_setting_v_layout->addWidget(m_ls_open_login_prompt_chk,0,Qt::AlignLeft|Qt::AlignTop);

    //订阅每日资讯
    m_ls_subscribe_to_daily_info_chk = new QCheckBox(m_login_setting_widget);
    m_ls_subscribe_to_daily_info_chk->setObjectName(QStringLiteral("m_ls_subscribe_to_daily_info_chk"));
    m_ls_subscribe_to_daily_info_chk->show();

    m_ls_setting_v_layout->addWidget(m_ls_subscribe_to_daily_info_chk,0,Qt::AlignLeft|Qt::AlignTop);

    m_ls_setting_v_layout->addStretch(0);

    m_ls_main_h_layout->addLayout(m_ls_setting_v_layout);
    m_ls_main_h_layout->addStretch(0);


}

void BasicSettingTabPageWidget::init_main_pannel_setting_widget()
{
    m_main_pannel_setting_widget = new QWidget(m_scroll_contents_widget);
    m_main_pannel_setting_widget->setObjectName(QStringLiteral("m_main_pannel_setting_widget"));
    m_main_pannel_setting_widget->setGeometry(QRect(0, 300, 600, 180));
    m_main_pannel_setting_widget->setStyleSheet(QStringLiteral("background-color:rgba(255,0,240,255);"));
    m_main_pannel_setting_widget->show();

    m_mps_main_h_layout = new QHBoxLayout(m_main_pannel_setting_widget);
    m_mps_main_h_layout->setObjectName(QStringLiteral("m_mps_main_h_layout"));
    m_mps_main_h_layout->setSpacing(0);
    m_mps_main_h_layout->setContentsMargins(SETTING_PANNEL_RIGHT_SCROLL_AREA_LEFT_MARGIN, SETTING_PANNEL_RIGHT_SCROLL_AREA_TOP_MARGIN, 0, 0);


    m_mps_category_lbl = new QLabel(m_main_pannel_setting_widget);
    m_mps_category_lbl->setObjectName(QStringLiteral("m_mps_category_lbl"));
    m_mps_category_lbl->setFixedWidth(SETTING_PANNEL_RIGHT_SCROLL_AREA_CATEGORY_LABEL_WIDTH);
    m_mps_category_lbl->show();

    m_mps_main_h_layout->addWidget(m_mps_category_lbl,0,Qt::AlignLeft|Qt::AlignTop);

    m_mps_setting_v_layout = new QVBoxLayout(m_main_pannel_setting_widget);
    m_mps_setting_v_layout->setObjectName(QStringLiteral("m_mps_setting_v_layout"));
    m_mps_setting_v_layout->setSpacing(SETTING_PANNEL_RIGHT_SCROLL_AREA_SPACE);

    m_mps_display_at_the_front_chk = new QCheckBox(m_main_pannel_setting_widget);
    m_mps_display_at_the_front_chk->setObjectName(QStringLiteral("m_mps_display_at_the_front_chk"));
    m_mps_display_at_the_front_chk->show();

    m_mps_setting_v_layout->addWidget(m_mps_display_at_the_front_chk,0,Qt::AlignLeft|Qt::AlignTop);

    m_mps_auto_hide_when_docked_on_desktop_edge_chk = new QCheckBox(m_main_pannel_setting_widget);
    m_mps_auto_hide_when_docked_on_desktop_edge_chk->setObjectName(QStringLiteral("m_mps_auto_hide_when_docked_on_desktop_edge_chk"));
    m_mps_auto_hide_when_docked_on_desktop_edge_chk->show();

    m_mps_setting_v_layout->addWidget(m_mps_auto_hide_when_docked_on_desktop_edge_chk,0,Qt::AlignLeft|Qt::AlignTop);

    m_mps_show_icon_in_taskbar_notification_area_chk = new QCheckBox(m_main_pannel_setting_widget);
    m_mps_show_icon_in_taskbar_notification_area_chk->setObjectName(QStringLiteral("m_mps_show_icon_in_taskbar_notification_area_chk"));
    m_mps_show_icon_in_taskbar_notification_area_chk->show();

    m_mps_setting_v_layout->addWidget(m_mps_show_icon_in_taskbar_notification_area_chk,0,Qt::AlignLeft|Qt::AlignTop);

    m_mps_close_main_pannel_intro_lbl = new QLabel(m_main_pannel_setting_widget);
    m_mps_close_main_pannel_intro_lbl->setObjectName(QStringLiteral("m_mps_close_main_pannel_intro_lbl"));

    m_mps_setting_v_layout->addWidget(m_mps_close_main_pannel_intro_lbl,0,Qt::AlignLeft|Qt::AlignTop);


    m_mps_hide_to_taskbar_chk = new QCheckBox(m_main_pannel_setting_widget);
    m_mps_hide_to_taskbar_chk->setObjectName(QStringLiteral("m_mps_hide_to_taskbar_chk"));
    m_mps_hide_to_taskbar_chk->show();

    m_mps_setting_v_layout->addWidget(m_mps_hide_to_taskbar_chk,0,Qt::AlignLeft|Qt::AlignTop);

    m_mps_quit_chk = new QCheckBox(m_main_pannel_setting_widget);
    m_mps_quit_chk->setObjectName(QStringLiteral("m_mps_quit_chk"));
    m_mps_quit_chk->show();

    m_mps_setting_v_layout->addWidget(m_mps_quit_chk,0,Qt::AlignLeft|Qt::AlignTop);

    m_mps_setting_v_layout->addStretch(0);

    m_mps_main_h_layout->addLayout(m_mps_setting_v_layout);
    m_mps_main_h_layout->addStretch(0);

}

void BasicSettingTabPageWidget::init_remind_settting_widget()
{
    //提醒设置页
    m_remind_settting_widget = new QWidget(m_scroll_contents_widget);
    m_remind_settting_widget->setObjectName(QStringLiteral("m_remind_settting_widget"));
    m_remind_settting_widget->setStyleSheet(QStringLiteral("background-color:rgba(255,255,0,255);"));
    m_remind_settting_widget->setGeometry(QRect(0, 600, 600, 180));
    m_remind_settting_widget->show();

    //提醒页水平布局，总体布局
    m_ms_main_h_layout = new QHBoxLayout(m_remind_settting_widget);
    m_ms_main_h_layout->setContentsMargins(SETTING_PANNEL_RIGHT_SCROLL_AREA_LEFT_MARGIN, SETTING_PANNEL_RIGHT_SCROLL_AREA_TOP_MARGIN, 0, 0);


    //提醒页左侧的类型项名称--提醒
    m_ms_category_lbl = new QLabel();
    m_ms_category_lbl->setObjectName(QStringLiteral("m_ms_category_lbl"));
    m_ms_category_lbl->setFixedWidth(SETTING_PANNEL_RIGHT_SCROLL_AREA_CATEGORY_LABEL_WIDTH);
    m_ms_category_lbl->show();

    //提醒页右侧具体设置的垂直布局，所有设置均在此布局下面
    m_ms_main_h_layout->addWidget(m_ms_category_lbl,0,Qt::AlignLeft|Qt::AlignTop);

    m_ms_setting_v_layout = new QVBoxLayout();
    m_ms_setting_v_layout->setSpacing(SETTING_PANNEL_RIGHT_SCROLL_AREA_SPACE);

    //会话消息提醒
    m_ms_session_msg_chk = new QCheckBox(m_remind_settting_widget);
    m_ms_session_msg_chk->setObjectName(QStringLiteral("m_ms_session_msg_chk"));
    m_ms_session_msg_chk->show();

    m_ms_setting_v_layout->addWidget(m_ms_session_msg_chk,0,Qt::AlignLeft|Qt::AlignTop);

    //Android设置连接提醒
    m_ms_android_device_conn_chk = new QCheckBox(m_remind_settting_widget);
    m_ms_android_device_conn_chk->setObjectName(QStringLiteral("m_ms_android_device_conn_chk"));
    m_ms_android_device_conn_chk->show();

    m_ms_setting_v_layout->addWidget(m_ms_android_device_conn_chk,0,Qt::AlignLeft|Qt::AlignTop);


    //Android设置连接提醒说明
    m_ms_android_device_conn_intro_lbl = new QLabel(m_remind_settting_widget);
    m_ms_android_device_conn_intro_lbl->setObjectName(QStringLiteral("m_ms_android_device_conn_intro_lbl"));
    m_ms_android_device_conn_intro_lbl->show();

    m_ms_setting_v_layout->addWidget(m_ms_android_device_conn_intro_lbl,0,Qt::AlignLeft|Qt::AlignTop);

    m_ms_setting_v_layout->addStretch(0);

    m_ms_main_h_layout->addLayout(m_ms_setting_v_layout);
    m_ms_main_h_layout->addStretch(0);
}


void BasicSettingTabPageWidget::init_app_update_setting_widget()
{
    //软件更新设置页
    m_app_update_setting_widget = new QWidget(m_scroll_contents_widget);
    m_app_update_setting_widget->setObjectName(QStringLiteral("m_app_update_setting_widget"));
    m_app_update_setting_widget->setStyleSheet(QStringLiteral("background-color:rgba(255,255,0,255);"));
    m_app_update_setting_widget->setGeometry(QRect(0, 900, 600, 180));//所这个设置均有问题
    m_app_update_setting_widget->show();

    //软件更新页水平布局，总体布局
    m_aus_main_h_layout = new QHBoxLayout(m_app_update_setting_widget);
    m_aus_main_h_layout->setContentsMargins(SETTING_PANNEL_RIGHT_SCROLL_AREA_LEFT_MARGIN, SETTING_PANNEL_RIGHT_SCROLL_AREA_TOP_MARGIN, 0, 0);


    //软件更新页左侧的类型项名称--软件更新
    m_aus_category_lbl = new QLabel();
    m_aus_category_lbl->setObjectName(QStringLiteral("m_aus_category_lbl"));
    m_aus_category_lbl->setFixedWidth(SETTING_PANNEL_RIGHT_SCROLL_AREA_CATEGORY_LABEL_WIDTH);
    m_aus_category_lbl->show();

    //软件更新页右侧具体设置的垂直布局，所有设置均在此布局下面
    m_aus_main_h_layout->addWidget(m_aus_category_lbl,0,Qt::AlignLeft|Qt::AlignTop);

    m_aus_setting_v_layout = new QVBoxLayout();
    m_aus_setting_v_layout->setSpacing(SETTING_PANNEL_RIGHT_SCROLL_AREA_SPACE);


    m_aus_update_mode_title_lbl = new QLabel(m_app_update_setting_widget);
    m_aus_update_mode_title_lbl->setObjectName(QStringLiteral("m_aus_update_mode_title_lbl"));
    m_aus_update_mode_title_lbl->show();

    m_aus_setting_v_layout->addWidget(m_aus_update_mode_title_lbl,0,Qt::AlignLeft|Qt::AlignTop);


    //有更新时自动为我安装（推荐）
    m_aus_auto_update_rbtn = new QRadioButton(m_app_update_setting_widget);
    m_aus_auto_update_rbtn->setObjectName(QStringLiteral("m_aus_auto_update_rbtn"));
    m_aus_auto_update_rbtn->show();

    m_aus_setting_v_layout->addWidget(m_aus_auto_update_rbtn,0,Qt::AlignLeft|Qt::AlignTop);

    //有更新时自动为我安装（推荐）--说明
    m_aus_auto_update_intro_lbl = new QLabel(m_app_update_setting_widget);
    m_aus_auto_update_intro_lbl->setObjectName(QStringLiteral("m_aus_auto_update_intro_lbl"));
    m_aus_auto_update_intro_lbl->show();

    m_aus_setting_v_layout->addWidget(m_aus_auto_update_intro_lbl,0,Qt::AlignLeft|Qt::AlignTop);

    //有更新时不安装，但提醒我
    m_aus_manual_update_rbtn = new QRadioButton(m_app_update_setting_widget);
    m_aus_manual_update_rbtn->setObjectName(QStringLiteral("m_aus_manual_update_rbtn"));
    m_aus_manual_update_rbtn->show();

    m_aus_setting_v_layout->addWidget(m_aus_manual_update_rbtn,0,Qt::AlignLeft|Qt::AlignTop);

    //有更新时不安装，但提醒我--说明
    m_aus_manual_update_intro_lbl = new QLabel(m_app_update_setting_widget);
    m_aus_manual_update_intro_lbl->setObjectName(QStringLiteral("m_aus_manual_update_intro_lbl"));
    m_aus_manual_update_intro_lbl->show();

    m_aus_setting_v_layout->addWidget(m_aus_manual_update_intro_lbl,0,Qt::AlignLeft|Qt::AlignTop);

    m_aus_setting_v_layout->addStretch(0);

    m_aus_main_h_layout->addLayout(m_aus_setting_v_layout);
    m_aus_main_h_layout->addStretch(0);

}


void BasicSettingTabPageWidget::onScrollAreaValueChanged(int value)
{

    Q_UNUSED(value);
    QListWidgetItem *m_login_setting_item = this->m_left_category_list_widget->item(0);
    QListWidgetItem *m_main_pannel_setting_item = this->m_left_category_list_widget->item(1);
    QListWidgetItem *m_remind_settting_item = this->m_left_category_list_widget->item(2);
    QListWidgetItem *m_app_update_setting_item = this->m_left_category_list_widget->item(3);

    if(m_login_setting_widget && m_main_pannel_setting_widget && m_remind_settting_widget && m_app_update_setting_widget)
    {
        if(!this->m_login_setting_widget->visibleRegion().isEmpty())
        {
            m_login_setting_item->setSelected(true);
            return;
        }else
        {
            m_login_setting_item->setSelected(false);
        }

        if(!this->m_main_pannel_setting_widget->visibleRegion().isEmpty())
        {
            m_main_pannel_setting_item->setSelected(true);
            return;
        }else
        {
            m_main_pannel_setting_item->setSelected(false);
        }

        if(!this->m_remind_settting_widget->visibleRegion().isEmpty())
        {
            m_remind_settting_item->setSelected(true);
            return;
        }else
        {
            m_remind_settting_item->setSelected(false);
        }

        if(!this->m_app_update_setting_widget->visibleRegion().isEmpty())
        {
            m_app_update_setting_item->setSelected(true);
            return;
        }else
        {
            m_app_update_setting_item->setSelected(false);
        }


    }
}

void BasicSettingTabPageWidget::onListWidgetItemClicked(QListWidgetItem *item)
{
    QString str_item_text = item->text();
    QPoint widget_pos;

    if(str_item_text == QStringLiteral("登录"))
    {
        widget_pos = this->m_login_setting_widget->pos();
        this->m_right_setting_scroll_area->verticalScrollBar()->setSliderPosition(widget_pos.y());
    }else if(str_item_text == QStringLiteral("主面板"))
    {
        widget_pos = this->m_main_pannel_setting_widget->pos();
        this->m_right_setting_scroll_area->verticalScrollBar()->setSliderPosition(widget_pos.y());

    }else if(str_item_text == QStringLiteral("提醒"))
    {
        widget_pos = this->m_remind_settting_widget->pos();
        this->m_right_setting_scroll_area->verticalScrollBar()->setSliderPosition(widget_pos.y());

    }else if(str_item_text == QStringLiteral("软件更新"))
    {
        widget_pos = this->m_app_update_setting_widget->pos();
        this->m_right_setting_scroll_area->verticalScrollBar()->setSliderPosition(widget_pos.y());

    }
}


void BasicSettingTabPageWidget::retranslateUi()
{
    //向左侧ListWidget添加数据
    m_left_category_list_widget->addItem(QStringLiteral("登录"));
    m_left_category_list_widget->addItem(QStringLiteral("主面板"));
    m_left_category_list_widget->addItem(QStringLiteral("提醒"));
    m_left_category_list_widget->addItem(QStringLiteral("软件更新"));

    m_ls_category_lbl->setText(QStringLiteral("登录："));
    m_ls_auto_start_chk->setText(QStringLiteral("开机时自动启动程序"));
    m_ls_open_login_prompt_chk->setText(QStringLiteral("总是打开登录提示"));
    m_ls_subscribe_to_daily_info_chk->setText(QStringLiteral("订阅每日资讯"));

    m_mps_category_lbl->setText(QStringLiteral("主面板："));
    m_mps_display_at_the_front_chk->setText(QStringLiteral("始终保持在最前端"));
    m_mps_auto_hide_when_docked_on_desktop_edge_chk->setText(QStringLiteral("靠在桌面边缘时自动隐藏"));
    m_mps_show_icon_in_taskbar_notification_area_chk->setText(QStringLiteral("在任务栏通知区域显示图标"));
    m_mps_close_main_pannel_intro_lbl->setText(QStringLiteral("关闭主面板时:"));
    m_mps_hide_to_taskbar_chk->setText(QStringLiteral("隐藏到任务栏通知区域，不退出程序"));
    m_mps_quit_chk->setText(QStringLiteral("退出程序"));

    m_ms_category_lbl->setText(QStringLiteral("提醒："));
    m_ms_session_msg_chk->setText(QStringLiteral("会话消息提醒"));
    m_ms_android_device_conn_chk->setText(QStringLiteral("Android设置连接提醒"));
    m_ms_android_device_conn_intro_lbl->setText(QStringLiteral("当插入Android设备时，提醒安装或更新程序"));

    m_aus_category_lbl->setText(QStringLiteral("软件更新"));
    m_aus_update_mode_title_lbl->setText(QStringLiteral("你可以选择本台计算机上程序的更新方式："));
    m_aus_auto_update_rbtn->setText(QStringLiteral("有更新时自动为我安装（推荐）"));
    m_aus_auto_update_intro_lbl->setText(QStringLiteral("当程序有更新时，智能选择最佳的软件更新方案，自动完成更新的下载\n与安装，省心省力"));
    m_aus_manual_update_rbtn->setText(QStringLiteral("有更新时不安装，但提醒我"));
    m_aus_manual_update_intro_lbl->setText(QStringLiteral("此方式不影响安全补丁等重要更新的自动安装"));


}


bool BasicSettingTabPageWidget::eventFilter(QObject *watched, QEvent *event)
{
    //QAbstractButton *abs_btn = qobject_cast<QAbstractButton*>(sender());//获取发射信号的对象

    if(watched->inherits("QCheckBox"))
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                qDebug("The Left Button Event!");
                //QCheckBox *chk_btn = qobject_cast<QCheckBox*>(sender());//获取发射信号的对象
                QCheckBox *chk_btn = qobject_cast<QCheckBox*>(watched);//转化为相应类型
                emit chk_btn->click();

                if(chk_btn->checkState() == Qt::Checked)
                {
                    Utils::SettingsUtils::save_config_data_to_ini_file(Utils::APP_SYSTEM_CONFIG_INI_FILE,
                                                                                 "config",chk_btn->objectName(),QString::number(Qt::Checked));
                }else
                {
                    Utils::SettingsUtils::save_config_data_to_ini_file(Utils::APP_SYSTEM_CONFIG_INI_FILE,
                                                                                 "config",chk_btn->objectName(),QString::number(Qt::Unchecked));
                }

                return true;

            }

        }
    }


//    if(watched == m_ls_auto_start_chk)
//    {
//        if(event->type() == QEvent::MouseButtonPress)
//        {
//            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
//            if(mouseEvent->button() == Qt::LeftButton)
//            {
//                qDebug("The Left Button Event!");
//                QCheckBox *chk_btn = qobject_cast<QCheckBox*>(watched);
//                emit chk_btn->click();
//                if(chk_btn->checkState() == Qt::Checked)
//                {
//                    Utils::SettingsUtils::save_config_data_to_ini_file(Utils::APP_SYSTEM_CONFIG_INI_FILE,
//                                                                                 "config","is_auto_start",QString::number(Qt::Checked));
//                }else
//                {
//                    Utils::SettingsUtils::save_config_data_to_ini_file(Utils::APP_SYSTEM_CONFIG_INI_FILE,
//                                                                                 "config","is_auto_start",QString::number(Qt::Unchecked));
//                }

//                return true;

//            }

//            return false;
//        }
//    }

    return QWidget::eventFilter(watched,event);
}
