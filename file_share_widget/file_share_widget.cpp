#include "file_share_widget.h"

FileShareWidget::FileShareWidget(QWidget *parent) : DraggableWidget(parent)
{
    this->setFixedSize(SETTING_PANNEL_WIDTH,SETTING_PANNEL_HEIGHT);
    this->setupUi();
    this->retranslateUi();

    connect(m_dialog_title_widget,SIGNAL(showMinimize()),this,SLOT(showMinimized()));//最小化
    connect(m_dialog_title_widget,SIGNAL(closeWidget()),this,SLOT(close()));//关闭窗体
}

FileShareWidget::~FileShareWidget()
{

}

void FileShareWidget::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("FileShareWidget"));

    m_main_v_layout = new QVBoxLayout(this);
    m_main_v_layout->setObjectName(QStringLiteral("m_main_v_layout"));
    m_main_v_layout->setContentsMargins(0,0,0,0);
    m_main_v_layout->setSpacing(0);

    m_dialog_title_widget = new DialogTitleWidget();
    m_dialog_title_widget->setObjectName(QStringLiteral("m_dialog_title_widget"));


    m_main_v_layout->addWidget(m_dialog_title_widget,0,Qt::AlignTop);

    m_main_v_layout->addStretch(0);


}


void FileShareWidget::retranslateUi()
{

}

void FileShareWidget::onShowMinimize()
{
}

void FileShareWidget::onCloseWidget()
{
}
