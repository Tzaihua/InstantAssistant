#include "security_setting_tab_page_widget.h"

SecuritySettingTabPageWidget::SecuritySettingTabPageWidget(QWidget *parent) : QWidget(parent)
{
    this->setupUi();
    this->retranslateUi();

    //如果Item不为空，则显示第一条
    if(m_left_category_list_widget->count() > 0){
        m_left_category_list_widget->setCurrentRow(0);
    }


    connect(m_left_category_list_widget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onListWidgetItemClicked(QListWidgetItem*)));
    connect(m_right_setting_scroll_area->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(onScrollAreaValueChanged(int)));

}

SecuritySettingTabPageWidget::~SecuritySettingTabPageWidget()
{

}

void SecuritySettingTabPageWidget::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("SecuritySettingTabPageWidget"));

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

    init_password_setting_widget();

    m_scroll_contents_widget->resize(this->width(),400);

    init_msg_setting_widget();

    m_scroll_contents_widget->resize(this->width(),800);

    init_security_update_setting_widget();

    m_scroll_contents_widget->resize(this->width(),1200);

    m_main_h_layout->addWidget(m_right_setting_scroll_area);
    m_main_h_layout->addStretch(0);


    QMetaObject::connectSlotsByName(this);
}


void SecuritySettingTabPageWidget::init_password_setting_widget()
{
    m_password_setting_widget = new QWidget(m_scroll_contents_widget);
    m_password_setting_widget->setObjectName(QStringLiteral("m_password_setting_widget"));
    m_password_setting_widget->setStyleSheet(QStringLiteral("background-color:rgba(255,255,0,255);"));
    m_password_setting_widget->setGeometry(QRect(0, 0, 600, 60));
    m_password_setting_widget->show();

    m_pws_main_h_layout = new QHBoxLayout(m_password_setting_widget);
    m_pws_main_h_layout->setObjectName(QStringLiteral("m_pws_main_h_layout"));
    m_pws_main_h_layout->setContentsMargins(SETTING_PANNEL_RIGHT_SCROLL_AREA_LEFT_MARGIN, SETTING_PANNEL_RIGHT_SCROLL_AREA_TOP_MARGIN, 0, 0);

    m_pws_catetory_lbl = new QLabel(m_password_setting_widget);
    m_pws_catetory_lbl->setObjectName(QStringLiteral("m_pws_catetory_lbl"));
    m_pws_catetory_lbl->setFixedWidth(SETTING_PANNEL_RIGHT_SCROLL_AREA_CATEGORY_LABEL_WIDTH);
    m_pws_catetory_lbl->show();

    m_pws_main_h_layout->addWidget(m_pws_catetory_lbl,0,Qt::AlignLeft|Qt::AlignTop);

    m_pws_setting_v_layout = new QVBoxLayout();
    m_pws_setting_v_layout->setObjectName(QStringLiteral("m_pws_setting_v_layout"));
    m_pws_setting_v_layout->setSpacing(SETTING_PANNEL_RIGHT_SCROLL_AREA_SPACE);

    m_pws_intro_lbl = new QLabel(m_password_setting_widget);
    m_pws_intro_lbl->setObjectName(QStringLiteral("m_pws_intro_lbl"));
    m_pws_intro_lbl->show();

    m_pws_setting_v_layout->addWidget(m_pws_intro_lbl,0,Qt::AlignLeft|Qt::AlignTop);

    m_pws_remember_password_btn = new QPushButton(m_password_setting_widget);
    m_pws_remember_password_btn->setObjectName(QStringLiteral("m_pws_remember_password_btn"));
    m_pws_remember_password_btn->show();

    m_pws_setting_v_layout->addWidget(m_pws_remember_password_btn,0,Qt::AlignLeft|Qt::AlignTop);
    m_pws_setting_v_layout->addStretch(0);

    m_pws_main_h_layout->addLayout(m_pws_setting_v_layout);
    m_pws_main_h_layout->addStretch(0);

}

void SecuritySettingTabPageWidget::init_msg_setting_widget()
{

    m_msg_setting_widget = new QWidget(m_scroll_contents_widget);
    m_msg_setting_widget->setObjectName(QStringLiteral("m_msg_setting_widget"));
    m_msg_setting_widget->setGeometry(QRect(0, 300, 600, 60));
    m_msg_setting_widget->setStyleSheet(QStringLiteral("background-color:rgba(255,0,240,255);"));
    m_msg_setting_widget->show();

    m_ms_main_h_layout = new QHBoxLayout(m_msg_setting_widget);
    m_ms_main_h_layout->setObjectName(QStringLiteral("m_ms_main_h_layout"));
    m_ms_main_h_layout->setSpacing(0);
    m_ms_main_h_layout->setContentsMargins(SETTING_PANNEL_RIGHT_SCROLL_AREA_LEFT_MARGIN, SETTING_PANNEL_RIGHT_SCROLL_AREA_TOP_MARGIN, 0, 0);

    m_ms_category_lbl = new QLabel(m_msg_setting_widget);
    m_ms_category_lbl->setObjectName(QStringLiteral("m_ms_category_lbl"));
    m_ms_category_lbl->setFixedWidth(SETTING_PANNEL_RIGHT_SCROLL_AREA_CATEGORY_LABEL_WIDTH);
    m_ms_category_lbl->show();

    m_ms_main_h_layout->addWidget(m_ms_category_lbl,0,Qt::AlignLeft|Qt::AlignTop);

    m_ms_setting_v_layout = new QVBoxLayout();
    m_ms_setting_v_layout->setObjectName(QStringLiteral("m_ms_setting_v_layout"));
    m_ms_setting_v_layout->setSpacing(SETTING_PANNEL_RIGHT_SCROLL_AREA_SPACE);


    m_ms_auto_syn_chk = new QCheckBox(m_msg_setting_widget);
    m_ms_auto_syn_chk->setObjectName(QStringLiteral("m_ms_auto_syn_chk"));
    m_ms_auto_syn_chk->show();

    m_ms_setting_v_layout->addWidget(m_ms_auto_syn_chk,0,Qt::AlignLeft|Qt::AlignTop);

    m_ms_auto_del_chk = new QCheckBox(m_msg_setting_widget);
    m_ms_auto_del_chk->setObjectName(QStringLiteral("m_ms_auto_del_chk"));
    m_ms_auto_del_chk->show();

    m_ms_setting_v_layout->addWidget(m_ms_auto_del_chk,0,Qt::AlignLeft|Qt::AlignTop);
    m_ms_setting_v_layout->addStretch(0);

    m_ms_main_h_layout->addLayout(m_ms_setting_v_layout);
    m_ms_main_h_layout->addStretch(0);
}


void SecuritySettingTabPageWidget::init_security_update_setting_widget()
{
    m_security_update_setting_widget = new QWidget(m_scroll_contents_widget);
    m_security_update_setting_widget->setObjectName(QStringLiteral("m_security_update_setting_widget"));
    m_security_update_setting_widget->setGeometry(QRect(0, 600, 600, 60));
    m_security_update_setting_widget->setStyleSheet(QStringLiteral("background-color:rgba(0,240,240,255);"));
    m_security_update_setting_widget->show();

    m_su_main_h_layout = new QHBoxLayout(m_security_update_setting_widget);
    m_su_main_h_layout->setObjectName(QStringLiteral("m_su_main_h_layout"));
    m_su_main_h_layout->setSpacing(0);
    m_su_main_h_layout->setContentsMargins(SETTING_PANNEL_RIGHT_SCROLL_AREA_LEFT_MARGIN, SETTING_PANNEL_RIGHT_SCROLL_AREA_TOP_MARGIN, 0, 0);

    m_su_category_lbl = new QLabel(m_security_update_setting_widget);
    m_su_category_lbl->setObjectName(QStringLiteral("m_su_category_lbl"));
    m_su_category_lbl->setFixedWidth(SETTING_PANNEL_RIGHT_SCROLL_AREA_CATEGORY_LABEL_WIDTH);
    m_su_category_lbl->show();

    m_su_main_h_layout->addWidget(m_su_category_lbl,0,Qt::AlignLeft|Qt::AlignTop);

    m_su_setting_v_layout = new QVBoxLayout();
    m_su_setting_v_layout->setObjectName(QStringLiteral("m_su_setting_v_layout"));
    m_su_setting_v_layout->setSpacing(SETTING_PANNEL_RIGHT_SCROLL_AREA_SPACE);

    m_su_auto_update_rbtn = new QRadioButton(m_security_update_setting_widget);
    m_su_auto_update_rbtn->setObjectName(QStringLiteral("m_su_auto_update_rbtn"));
    m_su_auto_update_rbtn->show();

    m_su_setting_v_layout->addWidget(m_su_auto_update_rbtn,0,Qt::AlignLeft|Qt::AlignTop);

    m_su_manual_update_rbtn = new QRadioButton(m_security_update_setting_widget);
    m_su_manual_update_rbtn->setObjectName(QStringLiteral("m_su_manual_update_rbtn"));
    m_su_manual_update_rbtn->show();

    m_su_setting_v_layout->addWidget(m_su_manual_update_rbtn,0,Qt::AlignLeft|Qt::AlignTop);
    m_su_setting_v_layout->addStretch(0);

    m_su_main_h_layout->addLayout(m_su_setting_v_layout);
    m_su_main_h_layout->addStretch(0);


}

void SecuritySettingTabPageWidget::retranslateUi()
{
    m_left_category_list_widget->clear();
    //向左侧ListWidget添加数据
    m_left_category_list_widget->addItem(QStringLiteral("密码"));
    m_left_category_list_widget->addItem(QStringLiteral("消息记录"));
    m_left_category_list_widget->addItem(QStringLiteral("安全更新"));


    m_pws_catetory_lbl->setText(QStringLiteral("密码:"));
    m_pws_intro_lbl->setText(QStringLiteral("你没有设置记住登录密码"));
    m_pws_remember_password_btn->setText(QStringLiteral("取消记住登录密码"));

    m_ms_category_lbl->setText(QStringLiteral("消息记录:"));
    m_ms_auto_syn_chk->setText(QStringLiteral("登录时，自动同步消息"));
    m_ms_auto_del_chk->setText(QStringLiteral("退出时，自动删除"));

    m_su_category_lbl->setText(QStringLiteral("安全更新："));
    m_su_auto_update_rbtn->setText(QStringLiteral("有安全更新时，自动为我安装，无需提醒（推荐）"));
    m_su_manual_update_rbtn->setText(QStringLiteral("有安全更新时，提醒我，不自动安装"));
}

void SecuritySettingTabPageWidget::onListWidgetItemClicked(QListWidgetItem *item)
{
    QString str_item_text = item->text();
    QPoint widget_pos;

    if(str_item_text == QStringLiteral("密码"))
    {
        widget_pos = this->m_password_setting_widget->pos();
        this->m_right_setting_scroll_area->verticalScrollBar()->setSliderPosition(widget_pos.y());
    }

    if(str_item_text == QStringLiteral("消息记录"))
    {
        widget_pos = this->m_msg_setting_widget->pos();
        this->m_right_setting_scroll_area->verticalScrollBar()->setSliderPosition(widget_pos.y());

    }

    if(str_item_text == QStringLiteral("安全更新"))
    {
        widget_pos = this->m_security_update_setting_widget->pos();
        this->m_right_setting_scroll_area->verticalScrollBar()->setSliderPosition(widget_pos.y());

    }
}

void SecuritySettingTabPageWidget::onScrollAreaValueChanged(int value)
{
    Q_UNUSED(value);

    QListWidgetItem *m_password_setting_item = this->m_left_category_list_widget->item(0);
    QListWidgetItem *m_msg_setting_item = this->m_left_category_list_widget->item(1);
    QListWidgetItem *m_security_update_setting_item = this->m_left_category_list_widget->item(2);


    if(m_password_setting_widget && m_msg_setting_widget && m_security_update_setting_widget)
    {


        m_password_setting_item->setSelected(false);
        m_msg_setting_item->setSelected(false);
        m_security_update_setting_item->setSelected(false);

        if(!this->m_password_setting_widget->visibleRegion().isEmpty())
        {
            m_password_setting_item->setSelected(true);
            qDebug()<<QStringLiteral("m_password_setting_widget false");
            return;
        }

        if(!this->m_msg_setting_widget->visibleRegion().isEmpty())
        {
            m_msg_setting_item->setSelected(true);
            qDebug()<<QStringLiteral("m_msg_setting_widget true");
            return;
        }

        if(!this->m_security_update_setting_widget->visibleRegion().isEmpty())
        {
            m_security_update_setting_item->setSelected(true);
            qDebug()<<QStringLiteral("m_security_update_setting_widget");
            return;
        }

    }
}
