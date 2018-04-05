#include "dialog_title_widget.h"

DialogTitleWidget::DialogTitleWidget(QWidget *parent) : QWidget(parent)
{
    this->setupUi();
    this->retranslateUi();

    QPixmap pixmap(QStringLiteral(":/resources/logo-QQ.png"));
    this->m_logo_lbl->setPixmap(pixmap);
    this->m_logo_lbl->show();

    //设置背景
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QColor(22,154,218)));
    this->setPalette(palette);
    this->setAutoFillBackground(true);//当使用QPalette为窗口设定背景并使用QPalette::Window时必须调用setAutoFillBackground(true)


    //
    connect(m_min_btn,SIGNAL(clicked(bool)),this,SIGNAL(showMinimize()));//最小化窗体
    connect(m_close_btn,SIGNAL(clicked(bool)),this,SIGNAL(closeWidget()));//退出系统

    //最小化按钮是否可视
    connect(this,SIGNAL(VisualStatusForMinimizeBtnChanged(bool)),this->m_min_btn,SLOT(setVisible(bool)));

}

void DialogTitleWidget::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("DialogTitleWidget"));

    m_main_title_h_layout = new QHBoxLayout(this);
    m_main_title_h_layout->setSpacing(0);
    m_main_title_h_layout->setObjectName(QStringLiteral("m_main_title_h_layout"));
    m_main_title_h_layout->setContentsMargins(MAIN_PANNEL_LEFT_MARGIN, 0, 0, 0);
    m_logo_lbl = new QLabel(this);
    m_logo_lbl->setObjectName(QStringLiteral("m_logo_lbl"));

    m_main_title_h_layout->addWidget(m_logo_lbl);

    m_app_name_lbl = new QLabel(this);
    m_app_name_lbl->setObjectName(QStringLiteral("m_app_name_lbl"));
    m_app_name_lbl->setStyleSheet(QStringLiteral("QLabel{color:rgb(255,255,255);font-size:12px;font-weight:bold;font-family:Georgia,serif,宋体;}"));
    m_app_name_lbl->setContentsMargins(5,0,0,0);

    m_main_title_h_layout->addWidget(m_app_name_lbl);

    m_main_title_h_layout->addStretch(0);

    m_main_menu_btn = new QPushButton(this);
    m_main_menu_btn->setObjectName(QStringLiteral("m_main_menu_btn"));

    m_main_title_h_layout->addWidget(m_main_menu_btn);

    m_medal_btn = new QPushButton(this);
    m_medal_btn->setObjectName(QStringLiteral("m_medal_btn"));

    m_main_title_h_layout->addWidget(m_medal_btn,0,Qt::AlignTop);

    m_min_btn = new QPushButton(this);
    m_min_btn->setObjectName(QStringLiteral("m_min_btn"));

    m_main_title_h_layout->addWidget(m_min_btn,0,Qt::AlignTop);

    m_close_btn = new QPushButton(this);
    m_close_btn->setObjectName(QStringLiteral("m_close_btn"));

    m_main_title_h_layout->addWidget(m_close_btn,0,Qt::AlignTop);


    //retranslateUi();

    QMetaObject::connectSlotsByName(this);
}

void DialogTitleWidget::retranslateUi()
{
    //m_app_name_lbl->setText(tr("软件名称"));
    m_main_menu_btn->setText(QString());
    m_medal_btn->setText(QString());
    m_min_btn->setText(QString());
    m_close_btn->setText(QString());

}

QString DialogTitleWidget::getDialogTitle() const
{
    return this->m_app_name_lbl->text();
}

void DialogTitleWidget::setDialogTitle(const QString title)
{
    this->m_app_name_lbl->setText(title);
    emit DialogTitleChanged(title);
}

bool DialogTitleWidget::isVisualForMinimizeBtn() const
{
    return m_is_visual_for_minimize_btn;
}

void DialogTitleWidget::setVisualStatusForMinimizeBtn(const bool isVisual)
{
    this->m_is_visual_for_minimize_btn = isVisual;
    emit VisualStatusForMinimizeBtnChanged(isVisual);//发出可视状态改变信号
}
