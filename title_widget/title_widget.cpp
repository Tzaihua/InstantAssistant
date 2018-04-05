#include "title_widget.h"

TitleWidget::TitleWidget(QWidget *parent) : QWidget(parent)
{
    this->setupUi();
    this->retranslateUi();

    QPixmap pixmap(QStringLiteral(":/resources/logo-QQ.png"));
    this->m_logo_lbl->setPixmap(pixmap);
    this->m_logo_lbl->show();

    //
    connect(m_min_btn,SIGNAL(clicked(bool)),this,SIGNAL(showMinimize()));//最小化窗体
    //将退出信号传递到MainWidget处理
    connect(m_close_btn,SIGNAL(clicked(bool)),this,SIGNAL(closeWidget()));//退出系统
//    connect(m_close_btn,SIGNAL(clicked(bool)),qApp, SLOT(quit()));//退出系统

}

void TitleWidget::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("TitleWidget"));

    m_main_title_h_layout = new QHBoxLayout(this);
    m_main_title_h_layout->setSpacing(0);
    m_main_title_h_layout->setObjectName(QStringLiteral("m_main_title_h_layout"));
    m_main_title_h_layout->setContentsMargins(MAIN_PANNEL_LEFT_MARGIN, 0, 0, 0);
    m_logo_lbl = new QLabel(this);
    m_logo_lbl->setObjectName(QStringLiteral("m_logo_lbl"));

    m_main_title_h_layout->addWidget(m_logo_lbl);

    m_app_name_lbl = new QLabel(this);
    m_app_name_lbl->setObjectName(QStringLiteral("m_app_name_lbl"));

    m_main_title_h_layout->addWidget(m_app_name_lbl);

    m_main_title_h_layout->addStretch(0);

    m_main_menu_btn = new QPushButton(this);
    m_main_menu_btn->setObjectName(QStringLiteral("m_main_menu_btn"));

    m_main_title_h_layout->addWidget(m_main_menu_btn);

    m_medal_btn = new QPushButton(this);
    m_medal_btn->setObjectName(QStringLiteral("m_medal_btn"));

    m_main_title_h_layout->addWidget(m_medal_btn);

    m_min_btn = new QPushButton(this);
    m_min_btn->setObjectName(QStringLiteral("m_min_btn"));

    m_main_title_h_layout->addWidget(m_min_btn);

    m_close_btn = new QPushButton(this);
    m_close_btn->setObjectName(QStringLiteral("m_close_btn"));

    m_main_title_h_layout->addWidget(m_close_btn);


    //retranslateUi();

    QMetaObject::connectSlotsByName(this);
}

void TitleWidget::retranslateUi()
{
    //m_app_name_lbl->setText(tr("软件名称"));
    m_main_menu_btn->setText(QString());
    m_medal_btn->setText(QString());
    m_min_btn->setText(QString());
    m_close_btn->setText(QString());

}
