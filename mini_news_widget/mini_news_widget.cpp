#include "mini_news_widget.h"


MiniNewsWidget::MiniNewsWidget(QWidget *parent) : DraggableWidget(parent)
{
    this->setFixedWidth(Baijuhua::MINI_NEWS_WIDTH);
    this->setFixedHeight(Baijuhua::MINI_NEWS_HEIGHT);

    this->setWindowOpacity(Qt::transparent);//设置窗体为透明

    this->setupUi();
    this->retranslateUi();
    //m_web_engine_view->load(QUrl("http://sucai.flashline.cn/flash5/yinyue/1266908082_64342.swf"));
    QWebEnginePage *m_p_web_page = new QWebEnginePage(this);
    m_web_engine_view->setPage(m_p_web_page);
//    m_p_web_page->setUrl(QUrl("http://sucai.flashline.cn/flash5/yinyue/1266908082_64342.swf"));
    m_p_web_page->setUrl(QUrl("file:///D:/code_aliyun/INSTANT_ASSISTANT_TOOLKITS/applications/InstantAssistant/resources/default/weather_skin/1/main.swf"));
    m_p_web_page->settings()->setAttribute(QWebEngineSettings::PluginsEnabled,true);
//    QWebEngineSettings *settings = QWebEngineSettings::defaultSettings();
//    settings->setAttribute(QWebEngineSettings::PluginsEnabled,true);
//    settings->setAttribute(QWebEngineSettings::JavascriptEnabled,true);

    //用于渐变显示的定时器
    m_timer_show = new QTimer(this);
    //渐变显示
    connect(m_timer_show,SIGNAL(timeout()),this,SLOT(onGradientShow()));

    connect(m_dialog_title_widget,SIGNAL(showMinimize()),this,SLOT(showMinimized()));//最小化
    connect(m_dialog_title_widget,SIGNAL(closeWidget()),this,SLOT(close()));//关闭窗体

}
MiniNewsWidget::~MiniNewsWidget()
{

}

void MiniNewsWidget::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("MiniNewsWidget"));

    m_main_v_layout = new QVBoxLayout(this);
    m_main_v_layout->setObjectName(QStringLiteral("m_main_v_layout"));
    m_main_v_layout->setContentsMargins(0,0,0,0);
    m_main_v_layout->setSpacing(0);

    m_dialog_title_widget = new DialogTitleWidget();
    m_dialog_title_widget->setObjectName(QStringLiteral("m_dialog_title_widget"));

    m_main_v_layout->addWidget(m_dialog_title_widget,0,Qt::AlignTop);

    m_web_engine_view = new QWebEngineView(this);
    m_main_v_layout->addWidget(m_web_engine_view,0,Qt::AlignTop|Qt::AlignHCenter);


}

void MiniNewsWidget::retranslateUi()
{

}

void MiniNewsWidget::onShowMinimize()
{
}

void MiniNewsWidget::onCloseWidget()
{
}

void MiniNewsWidget::showEvent(QShowEvent *event)
{
    //开启一个局部的事件循环，让其执行3000ms后自己退出,
    //说明：http://blog.csdn.net/xi__q/article/details/37561039
    QEventLoop eventloop;
    QTimer::singleShot(10000, &eventloop, SLOT(quit()));
    eventloop.exec();
    m_timer_show->start(10);//定时器启动

    DraggableWidget::showEvent(event);
}

void MiniNewsWidget::onGradientShow()
{
    m_transparent += 0.01;
    if(m_transparent >= 1.0)
    {
        m_timer_show->stop();
    }
    else
    {
        setWindowOpacity(m_transparent);
    }
}
