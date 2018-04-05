#include "app_manager_widget.h"

AppManagerWidget::AppManagerWidget(QWidget *parent) : DraggableWidget(parent)
{
    this->setFixedWidth(APP_MANAGER_WIDTH);
    this->setFixedHeight(APP_MANAGER_HEIGHT);
    this->setupUi();
    this->retranslateUi();

    connect(m_dialog_title_widget,SIGNAL(showMinimize()),this,SLOT(showMinimized()));//最小化
    connect(m_dialog_title_widget,SIGNAL(closeWidget()),this,SLOT(close()));//关闭窗体

}
AppManagerWidget::~AppManagerWidget()
{

}

void AppManagerWidget::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("AppManagerWidget"));

    m_main_v_layout = new QVBoxLayout(this);
    m_main_v_layout->setObjectName(QStringLiteral("m_main_v_layout"));
    m_main_v_layout->setContentsMargins(0,0,0,0);
    m_main_v_layout->setSpacing(0);

    m_dialog_title_widget = new DialogTitleWidget();
    m_dialog_title_widget->setObjectName(QStringLiteral("m_dialog_title_widget"));

    m_main_v_layout->addWidget(m_dialog_title_widget,0,Qt::AlignTop);
    m_main_v_layout->addStretch(0);
}

void AppManagerWidget::retranslateUi()
{

}

void AppManagerWidget::onShowMinimize()
{
}

void AppManagerWidget::onCloseWidget()
{
}
