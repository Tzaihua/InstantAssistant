#include "secrecy_setting_tab_page_widget.h"

SecrecySettingTabPageWidget::SecrecySettingTabPageWidget(QWidget *parent) : QWidget(parent)
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


SecrecySettingTabPageWidget::~SecrecySettingTabPageWidget()
{

}

void SecrecySettingTabPageWidget::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("SecrecySettingTabPageWidget"));

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

    init_remote_desktop_setting_widget();

    m_scroll_contents_widget->resize(this->width(),400);

    m_main_h_layout->addWidget(m_right_setting_scroll_area);
    m_main_h_layout->addStretch(0);

    QMetaObject::connectSlotsByName(this);
}

void SecrecySettingTabPageWidget::init_remote_desktop_setting_widget()
{
    m_remote_desktop_setting_widget = new QWidget(m_scroll_contents_widget);
    m_remote_desktop_setting_widget->setObjectName(QStringLiteral("m_remote_desktop_setting_widget"));
    m_remote_desktop_setting_widget->setStyleSheet(QStringLiteral("background-color:rgba(255,255,0,255);"));
    m_remote_desktop_setting_widget->setGeometry(QRect(0, 0, 600, 60));
    m_remote_desktop_setting_widget->show();

    m_rds_main_h_layout = new QHBoxLayout(m_remote_desktop_setting_widget);
    m_rds_main_h_layout->setObjectName(QStringLiteral("m_rds_main_h_layout"));
    m_rds_main_h_layout->setContentsMargins(SETTING_PANNEL_RIGHT_SCROLL_AREA_LEFT_MARGIN, SETTING_PANNEL_RIGHT_SCROLL_AREA_TOP_MARGIN, 0, 0);

    m_rds_catetory_lbl = new QLabel(m_remote_desktop_setting_widget);
    m_rds_catetory_lbl->setObjectName(QStringLiteral("m_rds_catetory_lbl"));
    m_rds_catetory_lbl->setFixedWidth(SETTING_PANNEL_RIGHT_SCROLL_AREA_CATEGORY_LABEL_WIDTH);
    m_rds_catetory_lbl->show();

    m_rds_main_h_layout->addWidget(m_rds_catetory_lbl,0,Qt::AlignLeft|Qt::AlignTop);

    m_rds_setting_v_layout = new QVBoxLayout();
    m_rds_setting_v_layout->setObjectName(QStringLiteral("m_rds_setting_v_layout"));
    m_rds_setting_v_layout->setSpacing(SETTING_PANNEL_RIGHT_SCROLL_AREA_SPACE);

    m_rds_allow_remote_conn_chk = new QCheckBox(m_remote_desktop_setting_widget);
    m_rds_allow_remote_conn_chk->setObjectName(QStringLiteral("m_rds_allow_remote_conn_chk"));
    m_rds_allow_remote_conn_chk->show();

    m_rds_setting_v_layout->addWidget(m_rds_allow_remote_conn_chk,0,Qt::AlignLeft|Qt::AlignTop);

    m_rds_auto_accept_conn_req_chk = new QCheckBox(m_remote_desktop_setting_widget);
    m_rds_auto_accept_conn_req_chk->setObjectName(QStringLiteral("m_rds_auto_accept_conn_req_chk"));
    m_rds_auto_accept_conn_req_chk->show();

    m_rds_setting_v_layout->addWidget(m_rds_auto_accept_conn_req_chk,0,Qt::AlignLeft|Qt::AlignTop);
    m_rds_setting_v_layout->addStretch(0);

    m_rds_main_h_layout->addLayout(m_rds_setting_v_layout);
    m_rds_main_h_layout->addStretch(0);
}

void SecrecySettingTabPageWidget::retranslateUi()
{
    m_left_category_list_widget->clear();
    //向左侧ListWidget添加数据
    m_left_category_list_widget->addItem(QStringLiteral("远程桌面"));

    m_rds_catetory_lbl->setText(QStringLiteral("远程桌面:"));
    m_rds_allow_remote_conn_chk->setText(QStringLiteral("允许远程桌面连接本计算机"));
    m_rds_auto_accept_conn_req_chk->setText(QStringLiteral("自动接受连接请求（建议手动关闭windows自动睡眠和锁屏功能）"));

}

void SecrecySettingTabPageWidget::onListWidgetItemClicked(QListWidgetItem *item)
{
    QString str_item_text = item->text();
    QPoint widget_pos;

    if(str_item_text == QStringLiteral("远程桌面"))
    {
        widget_pos = this->m_remote_desktop_setting_widget->pos();
        this->m_right_setting_scroll_area->verticalScrollBar()->setSliderPosition(widget_pos.y());
    }

}

void SecrecySettingTabPageWidget::onScrollAreaValueChanged(int value)
{
    Q_UNUSED(value);

    QListWidgetItem *m_remote_desktop_setting_item = this->m_left_category_list_widget->item(0);

    if(m_remote_desktop_setting_widget)
    {
        m_remote_desktop_setting_item->setSelected(false);

        if(!this->m_remote_desktop_setting_widget->visibleRegion().isEmpty())
        {
            m_remote_desktop_setting_item->setSelected(true);
            qDebug()<<QStringLiteral("m_password_setting_widget false");
            return;
        }

    }
}
