#include "unread_msg_box_widget.h"

UnreadMsgBoxWidget::UnreadMsgBoxWidget(QWidget *parent) : DraggableWidget(parent)
{
    this->setFixedWidth(APP_MANAGER_WIDTH);
    this->setFixedHeight(APP_MANAGER_HEIGHT);
    this->setupUi();
    this->retranslateUi();


//    this->m_dialog_title_widget->setStyleSheet(QStringLiteral("background-color:rgba(22,154,218,255);"));

    connect(m_dialog_title_widget,SIGNAL(showMinimize()),this,SLOT(showMinimized()));//最小化
    connect(m_dialog_title_widget,SIGNAL(closeWidget()),this,SLOT(close()));//关闭窗体

}

UnreadMsgBoxWidget::~UnreadMsgBoxWidget()
{

}

void UnreadMsgBoxWidget::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("UnreadMsgBoxWidget"));

    m_main_v_layout = new QVBoxLayout(this);
    m_main_v_layout->setObjectName(QStringLiteral("m_main_v_layout"));
    m_main_v_layout->setContentsMargins(0,0,0,0);
    m_main_v_layout->setSpacing(0);

    m_dialog_title_widget = new DialogTitleWidget();
    m_dialog_title_widget->setObjectName(QStringLiteral("m_dialog_title_widget"));


    m_main_v_layout->addWidget(m_dialog_title_widget,0,Qt::AlignTop);
    m_main_v_layout->addStretch(0);
}

void UnreadMsgBoxWidget::retranslateUi()
{

}

void UnreadMsgBoxWidget::onShowMinimize()
{

}

void UnreadMsgBoxWidget::onCloseWidget()
{

}
