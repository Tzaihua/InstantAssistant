#include "instant_message_dialog.h"


InstantMessageDialog::InstantMessageDialog(QWidget *parent) : DraggableWidget(parent)
{
//    this->setFixedWidth(APP_MANAGER_WIDTH);
//    this->setFixedHeight(APP_MANAGER_HEIGHT);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);//指定窗口的置顶
    //this->setWindowModality(Qt::ApplicationModal);

    setFixedSize(300, 180);
    this->setupUi();
    this->retranslateUi();

    m_timer_show = new QTimer(this);
    m_timer_stay = new QTimer(this);
    m_timer_close = new QTimer(this);

    m_time_count = 0;
    m_transparent = 1.0;

    m_desktop_height = QApplication::desktop()->height();

    connect(m_timer_show, SIGNAL(timeout()), this, SLOT(onMove()));
    connect(m_timer_stay, SIGNAL(timeout()), this, SLOT(onStay()));
    connect(m_timer_close, SIGNAL(timeout()), this, SLOT(onClose()));

    connect(m_dialog_title_widget,SIGNAL(showMinimize()),this,SLOT(showMinimized()));//最小化
    connect(m_dialog_title_widget,SIGNAL(closeWidget()),this,SLOT(close()));//关闭窗体

}
InstantMessageDialog::~InstantMessageDialog()
{

}

void InstantMessageDialog::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("InstantMessageDialog"));

    m_main_v_layout = new QVBoxLayout(this);
    m_main_v_layout->setObjectName(QStringLiteral("m_main_v_layout"));
    m_main_v_layout->setContentsMargins(0,0,0,0);
    m_main_v_layout->setSpacing(0);

    m_dialog_title_widget = new DialogTitleWidget();
    m_dialog_title_widget->setObjectName(QStringLiteral("m_dialog_title_widget"));
    m_dialog_title_widget->setVisualStatusForMinimizeBtn(false);

    m_main_v_layout->addWidget(m_dialog_title_widget,0,Qt::AlignTop);

    m_content_label = new QLabel();
    m_content_label->setObjectName(QStringLiteral("m_content_label"));
    m_content_label->setContentsMargins(20,5,20,5);
    m_content_label->setWordWrap(true);
    m_content_label->setAlignment(Qt::AlignTop);
    m_main_v_layout->addWidget(m_content_label,0,Qt::AlignTop);

    m_main_v_layout->addStretch(0);


}

void InstantMessageDialog::retranslateUi()
{

}

void InstantMessageDialog::onShowMessage(QString title, QString content)
{
    //title没有弄
    m_dialog_title_widget->setDialogTitle(title);
    m_content_label->setText(content);
    this->showMessage();
}

void InstantMessageDialog::showMessage()
{
    m_time_count = 0;
    m_transparent = 1.0;
    m_desktop_height = QApplication::desktop()->height();
    m_timer_show->stop();
    m_timer_stay->stop();
    m_timer_close->stop();
    setWindowOpacity(1);
    QDesktopWidget *desktop = QApplication::desktop();
    QRect desk_rect = desktop->availableGeometry();
    normal_point.setX(desk_rect.width() - rect().width());
    normal_point.setY(desk_rect.height() - rect().height());
    move(normal_point.x(), normal_point.y());
    showNormal();
    m_timer_show->start(5);
}

void InstantMessageDialog::onMove()
{
    m_desktop_height--;
    move(normal_point.x(), m_desktop_height);
    if(m_desktop_height <= normal_point.y())
    {
        m_timer_show->stop();
        m_timer_stay->start(1000);
    }
}

void InstantMessageDialog::onStay()
{
    m_time_count++;
    if(m_time_count >= 9)
    {
        m_timer_stay->stop();
        m_timer_close->start(200);
    }
}

void InstantMessageDialog::onClose()
{
    m_transparent -= 0.1;
    if(m_transparent <= 0.0)
    {
        m_timer_close->stop();
        this->close();
    }
    else
    {
        setWindowOpacity(m_transparent);
    }
}

void InstantMessageDialog::onShowMinimize()
{
}

void InstantMessageDialog::onCloseWidget()
{

}
