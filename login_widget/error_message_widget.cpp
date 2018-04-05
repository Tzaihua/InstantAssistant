#include "error_message_widget.h"

ErrorMessageWidget::ErrorMessageWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedHeight(28);
    this->setFixedWidth(parent->width()-5);

    /**
     * QWidget的autoFillBackground属性  bool类型
     * 这个属性决定widget的背景色是否自动填充。
     * 如果bool为真，这个属性会在widget触发PaintEvent之前引起Qt填充QWidget的背景色。
     * 填充的颜色是由widget的QPalette::window颜色角色所决定的。
     * 如果该widget没有设置WA_OpaquePaintEvent属性或者WA_NoSystemBackground属性，
     * windows总是会使用QPalette::window颜色角色。
     * 注意:如果widget的父窗口有渐变的背景色填充，那么这个属性是不能被关闭的（也就是不能设置为false)。
     * 警告:混合使用此属性和Qt style sheet的时候需要注意，
     * 当一个widget拥有一个style sheet设置的背景色或者border-image，那么autoFillBackground属性自动关闭。
     * 该属性默认是关闭状态。
     *
     *
     * */

    this->setAutoFillBackground(true);

    this->setupUi();
    this->retranslateUi();

    QObject::connect(m_close_btn, SIGNAL(clicked()), this, SLOT(closeWidget()));
}

ErrorMessageWidget::~ErrorMessageWidget()
{

}

void ErrorMessageWidget::setupUi()
{

    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("ErrorMessageWidget"));

    m_main_h_layout = new QHBoxLayout(this);
    m_main_h_layout->setObjectName(QStringLiteral("m_main_h_layout"));
    m_main_h_layout->setContentsMargins(5,0,0,0);
    m_main_h_layout->setSpacing(0);

    //设置提示图片
    m_msg_label = new QLabel(this);
    m_msg_label->setObjectName(QStringLiteral("m_msg_label"));
    m_msg_label->setScaledContents(true);
    m_msg_label->setMaximumSize(28,28);
    m_msg_label->setMinimumSize(18,18);
    m_msg_label->setFixedSize(20,20);
    //m_msg_label->setStyleSheet("background-color: transparent;");

    m_main_h_layout->addWidget(m_msg_label,0,Qt::AlignLeft);
    m_main_h_layout->addStretch(0);

    //设置提示信息
    m_ask_label = new QLabel(this);
    m_ask_label->setObjectName(QStringLiteral("m_ask_label"));
    m_ask_label->setStyleSheet(QStringLiteral("background-color: transparent;"));
    m_ask_label->setAlignment(Qt::AlignCenter);
    m_main_h_layout->addWidget(m_ask_label,0,Qt::AlignLeft);
    m_main_h_layout->addStretch(0);

    //构建关闭按钮
     m_close_btn= new QToolButton(this);
     m_close_btn->setObjectName(QStringLiteral("m_close_btn"));
     QPixmap close_pix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
     m_close_btn->setIcon(close_pix);
     m_close_btn->setStyleSheet(QStringLiteral("QToolButton{background-color: transparent;}"));

     m_main_h_layout->addWidget(m_close_btn,0,Qt::AlignTop|Qt::AlignRight);


}

void ErrorMessageWidget::retranslateUi()
{
    this->m_ask_label->setText(QStringLiteral("测试"));
}

void ErrorMessageWidget::setTipInfo(QString info)
{
    //设置提示信息
    m_ask_label->setText(info);
}
void ErrorMessageWidget::setTipIcon(QPixmap pixmap)
{
    //QPixmap *pixmap = new QPixmap(QStringLiteral(":/resources/message_box/sysmessagebox_warningFile.png"));

    QPixmap scaled_pixmap  = pixmap.scaled(QSize(20,20),Qt::KeepAspectRatio);

    m_msg_label->setPixmap(scaled_pixmap);
}

//关闭按钮主要进行提示框的隐藏
bool ErrorMessageWidget::closeWidget()
{
    this->hide();
    return true;
}

void ErrorMessageWidget::paintEvent(QPaintEvent *event)
{
    //设置背景色透明
    QPalette palette;
    QColor color(190, 230, 250);
    color.setAlphaF(0.6);
    palette.setBrush(this->backgroundRole(), color);
    this->setPalette(palette);

    QWidget::paintEvent(event);
}

void ErrorMessageWidget::showInfomation(QString info)
{
    QPixmap *pixmap = new QPixmap(QStringLiteral(":/resources/message_box/sysmessagebox_inforFile.png"));

    this->setTipIcon(*pixmap);
    this->setTipInfo(info);
}

void ErrorMessageWidget::showWarning(QString info)
{
    QPixmap *pixmap = new QPixmap(QStringLiteral(":/resources/message_box/sysmessagebox_warningFile.png"));

    this->setTipIcon(*pixmap);
    this->setTipInfo(info);

    m_ask_label->setStyleSheet("color: red;");

}
