#include "about_dialog.h"

AboutDialog::AboutDialog(QWidget *parent) : DraggableWidget(parent)
{
    this->setFixedWidth(ABOUT_DIALOG_WIDTH);
    this->setFixedHeight(ABOUT_DIALOG_HEIGHT);

    this->setupUi();
    this->retranslateUi();

    connect(m_dialog_title_widget,SIGNAL(showMinimize()),this,SLOT(showMinimized()));//最小化
    connect(m_dialog_title_widget,SIGNAL(closeWidget()),this,SLOT(close()));//关闭窗体
    connect(m_official_website_btn,SIGNAL(clicked(bool)),this,SLOT(onOpenWebsite()));
    connect(m_user_agreement_btn,SIGNAL(clicked(bool)),this,SLOT(onOpenUserAgreement()));
    connect(m_ok_btn,SIGNAL(clicked(bool)),this,SLOT(close()));

}
AboutDialog::~AboutDialog()
{

}

void AboutDialog::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("AboutDialog"));

    m_main_v_layout = new QVBoxLayout(this);
    m_main_v_layout->setObjectName(QStringLiteral("m_main_v_layout"));
    m_main_v_layout->setContentsMargins(0,0,0,0);
    m_main_v_layout->setSpacing(0);

    m_dialog_title_widget = new DialogTitleWidget();
    m_dialog_title_widget->setObjectName(QStringLiteral("m_dialog_title_widget"));

    m_main_v_layout->addWidget(m_dialog_title_widget,0,Qt::AlignTop);

    m_app_pictorial = new QLabel();
    m_app_pictorial->setObjectName(QStringLiteral("m_app_pictorial"));
    m_app_pictorial->setFixedHeight(64);

    m_main_v_layout->addWidget(m_app_pictorial,0,Qt::AlignTop);


    init_center_widget();
    m_main_v_layout->addWidget(m_center_widget,0,Qt::AlignTop);

    m_main_v_layout->addStretch(0);

    //底部部件
    m_bottom_main_widget = new QWidget();
    m_bottom_main_widget->setObjectName(QStringLiteral("m_bottom_main_widget"));
    m_bottom_main_widget->setFixedHeight(34);
    m_bottom_main_widget->setStyleSheet(QStringLiteral("QWidget#m_bottom_main_widget{background-color:rgb(229,239,247);color:rgb(255,255,255);}"));

    m_bottom_h_layout = new QHBoxLayout(m_bottom_main_widget);
    m_bottom_h_layout->setObjectName(QStringLiteral("m_main_v_layout"));
    m_bottom_h_layout->setContentsMargins(0,0,8,0);
    m_bottom_h_layout->setSpacing(0);
    //确认按钮
    m_ok_btn = new QPushButton();
    m_ok_btn->setObjectName(QStringLiteral("m_ok_btn"));
    m_ok_btn->setFixedSize(70,22);
    m_bottom_h_layout->addWidget(m_ok_btn,0,Qt::AlignRight|Qt::AlignVCenter);
    m_ok_btn->setFlat(true);

    m_main_v_layout->addWidget(m_bottom_main_widget,0,Qt::AlignBottom);
}

void AboutDialog::retranslateUi()
{
    m_app_name_lbl->setText(QStringLiteral("QQ8.7(10001)"));
    m_app_company_lbl->setText(QStringLiteral("重庆市九龙坡区"));
    m_copyright_lbl->setText(QStringLiteral("Copyright")  + u8"\u00a9" + QStringLiteral("2015-2017 Baizhihua.All Rights Reserved."));
    m_official_website_btn->setText(QStringLiteral("http://www.qq.com"));
    m_user_agreement_btn->setText(QStringLiteral("查看用户协议"));
    m_ok_btn->setText(QStringLiteral("确定(&O)"));
}


void AboutDialog::init_center_widget()
{
    m_center_widget = new QWidget();

    m_center_v_layout = new QVBoxLayout(m_center_widget);
    m_center_v_layout->setSpacing(6);
    m_center_v_layout->setObjectName(QStringLiteral("m_center_v_layout"));
    m_center_v_layout->setContentsMargins(8, 0, 8, 0);

    //软件名称
    m_app_name_lbl = new QLabel();
    m_app_name_lbl->setObjectName(QStringLiteral("m_app_name_lbl"));

    m_center_v_layout->addWidget(m_app_name_lbl);

    //开发公司
    m_app_company_lbl = new QLabel();
    m_app_company_lbl->setObjectName(QStringLiteral("m_app_company_lbl"));

    m_center_v_layout->addWidget(m_app_company_lbl);

    //版权
    m_copyright_lbl = new QLabel();
    m_copyright_lbl->setObjectName(QStringLiteral("m_copyright_lbl"));

    m_center_v_layout->addWidget(m_copyright_lbl);

    m_center_h_layout = new QHBoxLayout();
    m_center_h_layout->setSpacing(6);
    m_center_h_layout->setObjectName(QStringLiteral("m_center_h_layout"));

    //官方网站
    m_official_website_btn = new QPushButton();
    m_official_website_btn->setObjectName(QStringLiteral("m_official_website_btn"));
    m_official_website_btn->setFlat(true);


    m_center_h_layout->addWidget(m_official_website_btn,0,Qt::AlignLeft);

    //查看用户协议
    m_user_agreement_btn = new QPushButton();
    m_user_agreement_btn->setObjectName(QStringLiteral("m_user_agreement_btn"));
    m_user_agreement_btn->setFlat(true);


    m_center_h_layout->addWidget(m_user_agreement_btn,0,Qt::AlignRight);

    m_center_v_layout->addLayout(m_center_h_layout);

    //其它声明
    m_other_statements_tb = new QTextBrowser();
    m_other_statements_tb->setObjectName(QStringLiteral("m_other_statements_tb"));

    m_center_v_layout->addWidget(m_other_statements_tb);


    QMetaObject::connectSlotsByName(m_center_widget);
}


void AboutDialog::onShowMinimize()
{
}

void AboutDialog::onCloseWidget()
{
}

void AboutDialog::onOpenWebsite()
{
    QDesktopServices::openUrl(QUrl(QStringLiteral("http://www.sina.com.cn/")));

}

void AboutDialog::onOpenUserAgreement()
{
    QDesktopServices::openUrl(QUrl(QStringLiteral("http://www.sina.com.cn/")));

}


void AboutDialog::read_license()
{
    QString str_app_dir = QApplication::applicationDirPath();
    QString str_license_file_path = str_app_dir+"/"+Baijuhua::APP_LICENSE_FILE+"/"+"icu";

    QFile file(str_license_file_path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        qDebug()<<str_license_file_path+QStringLiteral("文件打开出错");
        return;
    }

    QTextStream stream(&file);
    //stream.setCodec("UTF-8");//默认使用系统的本地编码，但可指定编码
    this->m_other_statements_tb->setText(stream.readAll());

    file.close();

}

void AboutDialog::showEvent(QShowEvent *event)
{
    read_license();
    DraggableWidget::showEvent(event);
}
