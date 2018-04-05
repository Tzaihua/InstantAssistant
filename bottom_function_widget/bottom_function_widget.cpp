#include "bottom_function_widget.h"

BottomFunctionWidget::BottomFunctionWidget(QWidget *parent) : QWidget(parent)
{
    setupUi();
    retranslateUi();

    connect(m_main_menu_tbtn,SIGNAL(clicked(bool)),this,SIGNAL(showMainMenu()));//显示主目录
    connect(m_open_app_center_tbtn,SIGNAL(clicked(bool)),this,SIGNAL(showAppManagerWidget()));//应用管理器
    connect(main_app_setting_tbtn,SIGNAL(clicked(bool)),this,SIGNAL(showSettingPannelWidget()));//设置中心
    connect(m_open_msg_mgr_tbtn,SIGNAL(clicked(bool)),this,SIGNAL(showMsgManagerWidget()));//消息管理器
    connect(m_file_share_tbtn,SIGNAL(clicked(bool)),this,SIGNAL(showFileShareWidget()));//文件共享
    connect(m_collection_tbtn,SIGNAL(clicked(bool)),this,SIGNAL(showCollectionWidget()));//收藏
}


void BottomFunctionWidget::setupUi()
{
    if (this->objectName().isEmpty())
            this->setObjectName(QStringLiteral("BottomFunctionWidget"));
    m_main_v_layout = new QVBoxLayout(this);
    m_main_v_layout->setObjectName(QStringLiteral("m_main_v_layout"));
    m_main_v_layout->setSpacing(0);
    m_main_v_layout->setContentsMargins(MAIN_PANNEL_LEFT_MARGIN, 0, MAIN_PANNEL_RIGHT_MARGIN, MAIN_PANNEL_BOTTOM_MARGIN);


    m_function_top_h_layout = new QHBoxLayout();
    m_function_top_h_layout->setSpacing(2);
    m_function_top_h_layout->setObjectName(QStringLiteral("m_function_top_h_layout"));

    m_weiyun_tbtn = new QToolButton();
    m_weiyun_tbtn->setObjectName(QStringLiteral("m_weiyun_tbtn"));

    m_function_top_h_layout->addWidget(m_weiyun_tbtn);

    m_function_top_h_layout->addStretch(0);

    m_app_mgr_tbtn = new QToolButton();
    m_app_mgr_tbtn->setObjectName(QStringLiteral("m_app_mgr_tbtn"));

    m_function_top_h_layout->addWidget(m_app_mgr_tbtn);


//    m_main_v_layout->addLayout(m_function_top_h_layout);

    m_function_bottom_h_layout = new QHBoxLayout();
    m_function_bottom_h_layout->setSpacing(2);
    m_function_bottom_h_layout->setObjectName(QStringLiteral("m_function_bottom_h_layout"));

    m_main_menu_tbtn = new FunctionButton(this);
    m_main_menu_tbtn->setObjectName(QStringLiteral("m_main_menu_tbtn"));
    m_main_menu_tbtn->set_normal_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/mainmenubutton/menu_btn_normal.png")));
    m_main_menu_tbtn->set_active_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/mainmenubutton/menu_btn_highlight.png")));
    m_main_menu_tbtn->set_selected_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/mainmenubutton/menu_btn_highlight.png")));


    m_function_bottom_h_layout->addWidget(m_main_menu_tbtn,0,Qt::AlignBottom);

    main_app_setting_tbtn = new FunctionButton(this);
    main_app_setting_tbtn->setObjectName(QStringLiteral("main_app_setting_tbtn"));
    main_app_setting_tbtn->set_normal_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/button/tools2_hover.png")));
    main_app_setting_tbtn->set_active_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/button/tools2_hover.png")));
    main_app_setting_tbtn->set_selected_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/button/tools_down.png")));



    m_function_bottom_h_layout->addWidget(main_app_setting_tbtn,0,Qt::AlignBottom);

    m_open_msg_mgr_tbtn = new FunctionButton(this);
    m_open_msg_mgr_tbtn->setObjectName(QStringLiteral("m_open_msg_mgr_tbtn"));
    m_open_msg_mgr_tbtn->set_normal_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/button/message_highlight.png")));
    m_open_msg_mgr_tbtn->set_active_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/button/message_down.png")));
    m_open_msg_mgr_tbtn->set_selected_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/button/message_down.png")));


    m_function_bottom_h_layout->addWidget(m_open_msg_mgr_tbtn,0,Qt::AlignBottom);

    m_file_share_tbtn = new FunctionButton(this);
    m_file_share_tbtn->setObjectName(QStringLiteral("m_file_share_tbtn"));
    m_file_share_tbtn->set_normal_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/button/filemanager_hover.png")));
    m_file_share_tbtn->set_active_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/button/filemanager_down.png")));
    m_file_share_tbtn->set_selected_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/button/filemanager_down.png")));


    m_function_bottom_h_layout->addWidget(m_file_share_tbtn,0,Qt::AlignBottom);

    m_collection_tbtn = new FunctionButton();//new QToolButton(this);
    m_collection_tbtn->setObjectName(QStringLiteral("m_collection_tbtn"));
    m_collection_tbtn->set_normal_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/button/myCollection_mainpanel2_hover.png")));
    m_collection_tbtn->set_active_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/button/myCollection_mainpanel2_down.png")));
    m_collection_tbtn->set_selected_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/button/myCollection_mainpanel2_down.png")));

    m_function_bottom_h_layout->addWidget(m_collection_tbtn,0,Qt::AlignBottom);

    m_function_bottom_h_layout->addStretch(0);

    m_open_app_center_tbtn = new FunctionButton(this);
    m_open_app_center_tbtn->setObjectName(QStringLiteral("m_open_app_center_tbtn"));
    m_open_app_center_tbtn->set_normal_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/appbox/appbox_mgr_btn.png")));
    m_open_app_center_tbtn->set_active_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/appbox/appbox_mgr_btn2.png")));
    m_open_app_center_tbtn->set_selected_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/appbox/appbox_mgr_btn2.png")));


    m_function_bottom_h_layout->addWidget(m_open_app_center_tbtn,0,Qt::AlignBottom);


    m_main_v_layout->addLayout(m_function_bottom_h_layout);


    QMetaObject::connectSlotsByName(this);
}

void BottomFunctionWidget::retranslateUi()
{
//    this->setWindowTitle(QApplication::translate("MainWidget", "MainWidget", 0));
//    m_weiyun_tbtn->setText(QApplication::translate("MainWidget", "...", 0));
//    m_app_mgr_tbtn->setText(QApplication::translate("MainWidget", "...", 0));
//    m_main_menu_tbtn->setText(QApplication::translate("MainWidget", "...", 0));
//    main_app_setting_tbtn->setText(QApplication::translate("MainWidget", "...", 0));
//    m_open_msg_mgr_tbtn->setText(QApplication::translate("MainWidget", "...", 0));
//    m_file_share_tbtn->setText(QApplication::translate("MainWidget", "...", 0));
//    m_collection_tbtn->setText(tr("23"));
//    m_open_app_center_tbtn->setText(QApplication::translate("MainWidget", "...", 0));

}
