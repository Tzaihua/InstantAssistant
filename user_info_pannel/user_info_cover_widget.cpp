#include "user_info_cover_widget.h"

UserInfoCoverWidget::UserInfoCoverWidget(QWidget *parent) : QWidget(parent)
{

    setupUi();
    retranslateUi();

    connect(m_user_info_box_tbtn,SIGNAL(clicked(bool)),this,SIGNAL(showUnreadMsgBoxWidget()));//消息盒子

//    this->m_signature_line_edit->installEventFilter(this);
//    this->m_user_space_tbtn->installEventFilter(this);




//通过遍历控件的方式
    QObjectList list = this->children();
    foreach (QObject *obj, list)
    {
        if(obj->metaObject()->className() == QStringLiteral("QWidget"))
        {
            QObjectList inner_list = obj->children();
            foreach (QObject *inner_obj, inner_list)
            {
                if(inner_obj->inherits("QToolButton"))
                {
                    QToolButton *t = qobject_cast<QToolButton*>(inner_obj);
                    if(t)
                    {
                        t->installEventFilter(this);
                    }
                }
            }
        }

    }

}

void UserInfoCoverWidget::mousePressEvent(QMouseEvent *event)
{
    //这儿处理，只能暂时让m_signature_line_edit在UserInfoCoverWidget内失去焦点，而未在整个面板内失去焦点
    if(m_signature_line_edit->hasFocus())
    {


        m_signature_line_edit->clearFocus();
    }
    QWidget::mousePressEvent(event);
}


void UserInfoCoverWidget::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("UserInfoCoverWidget"));

    //主布局
    m_main_v_layout = new QVBoxLayout(this);
    m_main_v_layout->setObjectName(QStringLiteral("m_main_v_layout"));
    m_main_v_layout->setSpacing(0);
    m_main_v_layout->setContentsMargins(MAIN_PANNEL_LEFT_MARGIN,0,MAIN_PANNEL_RIGHT_MARGIN,0);

    //水平顶部布局，不包含下面排app快捷启动按钮那行
    m_main_top_h_layout = new QHBoxLayout();
    m_main_top_h_layout->setObjectName(QStringLiteral("m_main_top_h_layout"));
    m_main_top_h_layout->setSpacing(0);
    m_main_top_h_layout->setContentsMargins(0,0,0,0);

    //用户信息左侧垂直布局,不包含右侧的天气按钮
    m_user_info_left_v_layout = new QVBoxLayout();
    m_user_info_left_v_layout->setObjectName(QStringLiteral("m_user_info_left_v_layout"));
    m_user_info_left_v_layout->setSpacing(0);
    m_user_info_left_v_layout->setContentsMargins(0,0,0,0);

    //用户信息水平布局，即，用户妮称，用户状态、等级按钮的布局
    m_user_info_h_layout = new QHBoxLayout();
    m_user_info_h_layout->setObjectName(QStringLiteral("m_user_info_h_layout"));
    m_user_info_h_layout->setSpacing(0);
    m_user_info_h_layout->setContentsMargins(0,0,0,0);

    //用户妮称
    m_user_nick_name_btn = new QPushButton(this);
    m_user_nick_name_btn->setObjectName(QStringLiteral("m_user_nick_name_btn"));

    m_user_info_h_layout->addWidget(m_user_nick_name_btn);

    //用户状态
    m_status_tbtn = new QToolButton(this);
    m_status_tbtn->setObjectName(QStringLiteral("m_status_tbtn"));
    m_status_tbtn->setToolButtonStyle(Qt::ToolButtonIconOnly);//只显示图标


    m_user_info_h_layout->addWidget(m_status_tbtn);

    //用户等级
    m_user_grade_tbtn = new QToolButton(this);
    m_user_grade_tbtn->setObjectName(QStringLiteral("m_user_grade_tbtn"));
    m_user_grade_tbtn->setToolButtonStyle(Qt::ToolButtonIconOnly);//只显示图标

    m_user_info_h_layout->addWidget(m_user_grade_tbtn);

    m_user_info_h_layout->addStretch(0);

    //将用户信息行部件加入用户信息左侧布局
    m_user_info_left_v_layout->addLayout(m_user_info_h_layout);

    //签名
    m_signature_line_edit = new SignatureLineEdit(this);
    m_signature_line_edit->setObjectName(QStringLiteral("m_signature_line_edit"));

    m_user_info_left_v_layout->addWidget(m_signature_line_edit);


    m_main_top_h_layout->addLayout(m_user_info_left_v_layout);

//    //天气
//    m_weather_lbl = new QLabel(this);
//    m_weather_lbl->setObjectName(QStringLiteral("m_weather_lbl"));
//    m_weather_lbl->setFixedSize(60,50);
//    QPixmap m_weather_pixmap(QStringLiteral(":/resources/default/weather_skin/res/Big_1.png"));
//    m_weather_lbl->setPixmap(m_weather_pixmap);
//    m_weather_lbl->show();

//    m_main_top_h_layout->addWidget(m_weather_lbl);


    m_main_v_layout->addLayout(m_main_top_h_layout);

    m_app_short_cut_widget = new QWidget(this);
    m_app_short_cut_widget->setObjectName(QStringLiteral("m_app_short_cut_widget"));

    m_app_short_cut_h_layout = new QHBoxLayout(m_app_short_cut_widget);
    m_app_short_cut_h_layout->setSpacing(2);
    m_app_short_cut_h_layout->setContentsMargins(0, 0, 0, 0);
    m_app_short_cut_h_layout->setObjectName(QStringLiteral("m_app_short_cut_h_layout"));
    m_app_short_cut_h_layout->setContentsMargins(0, 0, 0, 0);

    //用户空间管理
    m_user_space_tbtn = new FunctionButton(m_app_short_cut_widget);
    m_user_space_tbtn->setObjectName(QStringLiteral("m_user_space_tbtn"));
    m_user_space_tbtn->set_normal_pixmap(QPixmap(QStringLiteral(":/resources/default/mainhelp/ProductBlog.PNG")));
    m_user_space_tbtn->set_active_pixmap(QPixmap(QStringLiteral(":/resources/default/mainhelp/ProductBlog.PNG")));
    m_user_space_tbtn->set_selected_pixmap(QPixmap(QStringLiteral(":/resources/default/mainhelp/ProductBlog.PNG")));


    m_app_short_cut_h_layout->addWidget(m_user_space_tbtn,0,Qt::AlignLeft);

    //
    m_customer_center_tbtn = new FunctionButton(m_app_short_cut_widget);
    m_customer_center_tbtn->setObjectName(QStringLiteral("m_customer_center_tbtn"));
    m_customer_center_tbtn->set_normal_pixmap(QPixmap(QStringLiteral(":/resources/default/mainhelp/CustomerCenter.PNG")));
    m_customer_center_tbtn->set_active_pixmap(QPixmap(QStringLiteral(":/resources/default/mainhelp/CustomerCenter.PNG")));
    m_customer_center_tbtn->set_selected_pixmap(QPixmap(QStringLiteral(":/resources/default/mainhelp/CustomerCenter.PNG")));


    m_app_short_cut_h_layout->addWidget(m_customer_center_tbtn,0,Qt::AlignLeft);

    //
    m_menu_help_tbtn = new FunctionButton(m_app_short_cut_widget);
    m_menu_help_tbtn->setObjectName(QStringLiteral("m_menu_help_tbtn"));
    m_menu_help_tbtn->set_normal_pixmap(QPixmap(QStringLiteral(":/resources/default/mainhelp/menu_help.png")));
    m_menu_help_tbtn->set_active_pixmap(QPixmap(QStringLiteral(":/resources/default/mainhelp/menu_help.png")));
    m_menu_help_tbtn->set_selected_pixmap(QPixmap(QStringLiteral(":/resources/default/mainhelp/menu_help.png")));


    m_app_short_cut_h_layout->addWidget(m_menu_help_tbtn,0,Qt::AlignLeft);

    //
    m_question_and_advance_tbtn = new FunctionButton(m_app_short_cut_widget);
    m_question_and_advance_tbtn->setObjectName(QStringLiteral("m_question_and_advance_tbtn"));
    m_question_and_advance_tbtn->set_normal_pixmap(QPixmap(QStringLiteral(":/resources/default/mainhelp/QuestionAndAdvance.PNG")));
    m_question_and_advance_tbtn->set_active_pixmap(QPixmap(QStringLiteral(":/resources/default/mainhelp/QuestionAndAdvance.PNG")));
    m_question_and_advance_tbtn->set_selected_pixmap(QPixmap(QStringLiteral(":/resources/default/mainhelp/QuestionAndAdvance.PNG")));


    m_app_short_cut_h_layout->addWidget(m_question_and_advance_tbtn,0,Qt::AlignLeft);

    m_app_short_cut_h_layout->addStretch(0);

    //用户皮肤管理
    m_app_face_manager_tbtn = new FunctionButton(m_app_short_cut_widget);
    m_app_face_manager_tbtn->setObjectName(QStringLiteral("m_app_face_manager_tbtn"));
    m_app_face_manager_tbtn->set_normal_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/button/btn_skin_normal.png")));
    m_app_face_manager_tbtn->set_active_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/button/btn_Skin_highlight.png")));
    m_app_face_manager_tbtn->set_selected_pixmap(QPixmap(QStringLiteral(":/resources/default/mainpannel/button/btn_Skin_down.png")));


    m_app_short_cut_h_layout->addWidget(m_app_face_manager_tbtn,0,Qt::AlignRight);

    //用户消息盒子
    m_user_info_box_tbtn = new FunctionButton(m_app_short_cut_widget);
    m_user_info_box_tbtn->setObjectName(QStringLiteral("m_user_info_box_tbtn"));
    m_user_info_box_tbtn->set_normal_pixmap(QPixmap(QStringLiteral(":/resources/default/informationbox/Messagebox16_2.png")));
    m_user_info_box_tbtn->set_active_pixmap(QPixmap(QStringLiteral(":/resources/default/informationbox/Messagebox16_2.png")));
    m_user_info_box_tbtn->set_selected_pixmap(QPixmap(QStringLiteral(":/resources/default/informationbox/Messagebox16_2.png")));

    m_app_short_cut_h_layout->addWidget(m_user_info_box_tbtn,0,Qt::AlignRight);


    m_main_v_layout->addWidget(m_app_short_cut_widget,0,Qt::AlignBottom);


     QMetaObject::connectSlotsByName(this);
} // setupUi



void UserInfoCoverWidget::retranslateUi()
{
    //this->setWindowTitle(QApplication::translate("UserInfoCoverWidget", "UserInfoCoverWidget", 0));
    m_user_nick_name_btn->setText(QStringLiteral("Tzaihua"));
    this->m_signature_line_edit->setText(QStringLiteral("一生一事，一步一印，持之以恒，再来一次yyyyyyyyy"));
//    m_weather_lbl->setText(QApplication::translate("UserInfoCoverWidget", "TextLabel", 0));
//    m_user_space_tbtn->setText(QApplication::translate("UserInfoCoverWidget", "...", 0));
//    m_user_info_box_tbtn->setText(QApplication::translate("UserInfoCoverWidget", "...", 0));
} // retranslateUi


bool UserInfoCoverWidget::eventFilter(QObject *object, QEvent *event)
{
    //搜索结果与TAB页切换
    if (object != this->m_signature_line_edit)
    {
        switch (event->type()) {
        case QEvent::MouseButtonPress:
            this->m_signature_line_edit->clearFocus();
            break;
        default:
            break;
        }
    }

    return QWidget::eventFilter(object,event);
}
