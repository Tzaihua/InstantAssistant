#include "weather_info_floating_widget.h"

#define LOGINIPINTER "http://www.3322.org/dyndns/getip"

WeatherInfoFloatingWidget::WeatherInfoFloatingWidget(QWidget *parent) : DraggableWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);//指定窗口的置顶

    this->setFixedWidth(WEATHER_INFO_FLOATING_WIDGET_WIDTH);
    this->setFixedHeight(WEATHER_INFO_FLOATING_WIDGET_HEIGHT);

    //m_network_info_plugin == NULL;

    if(!on_load_plugin(m_network_info_plugin))
    {
        //如果无法加载插件
         qDebug()<<QStringLiteral("Could not load the NetworkInfoPluginInterface plugin.");
         QMessageBox::information(this,"Error","网络插件加载失败！");

    }else{
        qDebug()<<QStringLiteral("load the NetworkInfoPluginInterface plugin successful.");
    }


    m_is_flash_load_finished = false;

    this->setupUi();
    this->retranslateUi();

    m_weather_forecast_date_list << label_8 << label_9 << label_10;
    m_weather_forecast_temp_list << m_cur_mini_temperature_lbl << m_tomorrow_mini_temperature_lbl << m_after_tomorrow_mini_temperature_lbl;
    m_weather_forecast_type_list << m_cur_weather_logo_lbl << m_tomorrow_weather_logo_lbl << m_after_tomorrow_weather_logo_lbl;
    m_network_access_manager = new QNetworkAccessManager();

    on_load_city_keys();
    QString str_city_key =  to_parse_city_key(on_get_location_addr_by_internet_ip());
    to_parse_this_day_weather_report_by_xml(to_get_weather_report(str_city_key));

    to_parse_forecast_weather_report_by_json(to_get_forecast_weather_report(str_city_key));

    m_cur_temperature_lbl->setText(tr("%1℃").arg(m_weather_today.wendu));
    m_cur_location_lbl->setText(m_weather_today.city);
    //m_meteorology_lbl->setText(m_weather_today.);
    m_wind_lbl->setText(m_weather_today.fengxiang);

    for(int i=0;i<3;i++)
    {
        //m_weather_forecast_date_list[i]->setText(tr("%1").arg(m_weather_forecast[i].date));
        m_weather_forecast_temp_list[i]->setText(tr("%1/%2").arg(m_weather_forecast[i].low.split(" ").at(1)).arg(m_weather_forecast[i].high.split(" ").at(1)));
        m_weather_forecast_type_list[i]->setPixmap(QPixmap(tr(":/resources/default/weather_skin/old_res/%1.png").arg(m_weather_forecast[i].type)).scaled(60,50,Qt::KeepAspectRatioByExpanding));
        m_weather_forecast_type_list[i]->setToolTip(tr("%1 : %2/%3").arg(m_weather_forecast[i].type).arg(m_weather_forecast[i].fengli).arg(m_weather_forecast[i].fengxiang));
    }
    m_meteorology_lbl->setText(m_weather_forecast[0].type);

    m_widget_showing_timer = new QTimer(this);

    connect(m_widget_showing_timer,SIGNAL(timeout()),this,SLOT(hide()));

    connect(m_p_weather_flash_web_engine_view,SIGNAL(loadFinished(bool)),this,SLOT(onSetFlashLoadFinished(bool)));


}

WeatherInfoFloatingWidget::~WeatherInfoFloatingWidget()
{

//    if(m_network_info_plugin)
//    {
//        delete m_network_info_plugin;
//    }
//    m_network_info_plugin = NULL;

}

void WeatherInfoFloatingWidget::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("WeatherInfoFloatingWidget"));

    init_weather_info_up_widget();//主要是初始化天气信息组件面板，即m_p_weather_info_widget
    init_weather_info_bottom_widget();
    m_main_v_layout = new QVBoxLayout(this);

    //层叠布局
    m_main_s_layout = new QStackedLayout(this);
    m_main_s_layout->setStackingMode(QStackedLayout::StackAll);//将其层叠布局中的所有控件都置为显示状态
    m_main_s_layout->setContentsMargins(0,0,0,0);


    m_p_weather_flash_web_engine_view = new QWebEngineView(this);
    m_p_weather_flash_web_engine_view->setUrl(QUrl("file:///D:/code_aliyun/INSTANT_ASSISTANT_TOOLKITS/applications/InstantAssistant/resources/default/weather_skin/1/main.swf"));
    m_p_weather_flash_web_engine_view->settings()->setAttribute(QWebEngineSettings::PluginsEnabled,true);
    m_p_weather_flash_web_engine_view->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled,true);//支持JS

//    QWebEnginePage *m_p_weather_flash_web_engine_page = new QWebEnginePage(m_p_weather_flash_web_engine_view);
//    m_p_weather_flash_web_engine_view->setPage(m_p_weather_flash_web_engine_page);
//    m_p_weather_flash_web_engine_page->setUrl(QUrl("file:///D:/code_aliyun/INSTANT_ASSISTANT_TOOLKITS/applications/InstantAssistant/resources/default/weather_skin/1/main.swf"));
//    m_p_weather_flash_web_engine_page->settings()->setAttribute(QWebEngineSettings::PluginsEnabled,true);
//    QSize size =  m_p_weather_flash_web_engine_view->page()->contentsSize().toSize();
//    m_p_weather_flash_web_engine_view->setMaximumWidth(m_p_weather_flash_web_engine_view->width()*size.width()/m_p_weather_flash_web_engine_view->width());



    m_main_s_layout->addWidget(m_p_weather_info_widget);
    m_main_s_layout->addWidget(m_p_weather_flash_web_engine_view);

    m_main_v_layout->addLayout(m_main_s_layout);
    m_main_v_layout->addWidget(m_p_weather_info_bottom_widget);


    retranslateUi();

//    QMetaObject::connectSlotsByName(this);
}

void WeatherInfoFloatingWidget::init_weather_info_up_widget()
{

    //天气主要信息的层叠Widget
      m_p_weather_info_widget = new QWidget(this);

      //上端天气布局
      m_p_up_v_layout = new QVBoxLayout();//因需要做成层叠效果，故此处构造函数不再指定为this，QVBoxLayout(this)
      m_p_up_v_layout->setSpacing(6);
      m_p_up_v_layout->setContentsMargins(11, 11, 11, 11);
      m_p_up_v_layout->setObjectName(QStringLiteral("m_p_up_v_layout"));

      //顶部温度显示处布局
      m_top_h_layout = new QHBoxLayout();
      m_top_h_layout->setSpacing(6);
      m_top_h_layout->setObjectName(QStringLiteral("m_top_h_layout"));

      //当前温度
      m_cur_temperature_lbl = new QLabel();
      m_cur_temperature_lbl->setObjectName(QStringLiteral("m_cur_temperature_lbl"));
      m_cur_temperature_lbl->setStyleSheet("font-size:34px;font-family:Times New Roman;font-weight:bold;");

      m_top_h_layout->addWidget(m_cur_temperature_lbl);
      m_top_h_layout->addStretch(0);

      m_p_up_v_layout->addLayout(m_top_h_layout);

      //中间当前地市区布局
      m_center_local_h_layout = new QHBoxLayout();
      m_center_local_h_layout->setSpacing(6);
      m_center_local_h_layout->setObjectName(QStringLiteral("m_center_local_h_layout"));

      //当前地市
      m_cur_location_lbl = new QLabel();
      m_cur_location_lbl->setObjectName(QStringLiteral("m_cur_location_lbl"));

      m_center_local_h_layout->addWidget(m_cur_location_lbl);
      m_center_local_h_layout->addStretch(0);

      m_p_up_v_layout->addLayout(m_center_local_h_layout);

      //中间气象、风向布局
      m_center_wind_h_layout = new QHBoxLayout();
      m_center_wind_h_layout->setSpacing(6);
      m_center_wind_h_layout->setObjectName(QStringLiteral("m_center_wind_h_layout"));
      m_meteorology_lbl = new QLabel();
      m_meteorology_lbl->setObjectName(QStringLiteral("m_meteorology_lbl"));

      m_center_wind_h_layout->addWidget(m_meteorology_lbl);

      m_wind_lbl = new QLabel();
      m_wind_lbl->setObjectName(QStringLiteral("m_wind_lbl"));

      m_center_wind_h_layout->addWidget(m_wind_lbl);
      m_center_wind_h_layout->addStretch(0);

      m_p_up_v_layout->addLayout(m_center_wind_h_layout);

      //中间天气质量布局
      m_center_air_h_layout = new QHBoxLayout();
      m_center_air_h_layout->setSpacing(6);
      m_center_air_h_layout->setObjectName(QStringLiteral("m_center_air_h_layout"));
      //天气质量
      m_air_qulity_lbl = new QLabel();
      m_air_qulity_lbl->setObjectName(QStringLiteral("m_air_qulity_lbl"));

      m_center_air_h_layout->addWidget(m_air_qulity_lbl);

      label_6 = new QLabel();
      label_6->setObjectName(QStringLiteral("label_6"));

      m_center_air_h_layout->addWidget(label_6);

      m_pm25_lbl = new QLabel();
      m_pm25_lbl->setObjectName(QStringLiteral("m_pm25_lbl"));

      m_center_air_h_layout->addWidget(m_pm25_lbl);
      m_center_air_h_layout->addStretch(0);

      m_p_up_v_layout->addLayout(m_center_air_h_layout);

      //m_p_up_v_layout->addLayout(m_bottom_h_layout);

      m_p_weather_info_widget->setLayout(m_p_up_v_layout);

}


void WeatherInfoFloatingWidget::init_weather_info_bottom_widget()
{
    m_p_weather_info_bottom_widget = new QWidget(this);

    //底部连续三天天气布局
    m_bottom_h_layout = new QHBoxLayout(m_p_weather_info_bottom_widget);
    m_bottom_h_layout->setSpacing(6);
    m_bottom_h_layout->setObjectName(QStringLiteral("m_bottom_h_layout"));
    m_p_weather_info_bottom_widget->setLayout(m_bottom_h_layout);

    //今天
    m_cur_weather_v_layout = new QVBoxLayout();
    m_cur_weather_v_layout->setSpacing(6);
    m_cur_weather_v_layout->setObjectName(QStringLiteral("m_cur_weather_v_layout"));
    label_8 = new QLabel();
    label_8->setObjectName(QStringLiteral("label_8"));
    label_8->setAlignment(Qt::AlignHCenter);//文字显示在中间

    m_cur_weather_v_layout->addWidget(label_8);

    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setSpacing(6);
    horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
    m_cur_mini_temperature_lbl = new QLabel();
    m_cur_mini_temperature_lbl->setObjectName(QStringLiteral("m_cur_mini_temperature_lbl"));

    horizontalLayout_3->addWidget(m_cur_mini_temperature_lbl);


    m_cur_weather_v_layout->addLayout(horizontalLayout_3);

    m_cur_weather_logo_lbl = new QLabel();
    m_cur_weather_logo_lbl->setObjectName(QStringLiteral("m_cur_weather_logo_lbl"));
    m_cur_weather_logo_lbl->setFixedSize(60,50);

    m_cur_weather_v_layout->addWidget(m_cur_weather_logo_lbl);


    m_bottom_h_layout->addLayout(m_cur_weather_v_layout);

    //明天
    m_tomorrow_weather_v_layout = new QVBoxLayout();
    m_tomorrow_weather_v_layout->setSpacing(6);
    m_tomorrow_weather_v_layout->setObjectName(QStringLiteral("m_tomorrow_weather_v_layout"));
    label_9 = new QLabel();
    label_9->setObjectName(QStringLiteral("label_9"));
    label_9->setAlignment(Qt::AlignHCenter);//文字显示在中间


    m_tomorrow_weather_v_layout->addWidget(label_9);

    horizontalLayout_4 = new QHBoxLayout();
    horizontalLayout_4->setSpacing(6);
    horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
    m_tomorrow_mini_temperature_lbl = new QLabel();
    m_tomorrow_mini_temperature_lbl->setObjectName(QStringLiteral("m_tomorrow_mini_temperature_lbl"));

    horizontalLayout_4->addWidget(m_tomorrow_mini_temperature_lbl);

    m_tomorrow_weather_v_layout->addLayout(horizontalLayout_4);

    m_tomorrow_weather_logo_lbl = new QLabel();
    m_tomorrow_weather_logo_lbl->setObjectName(QStringLiteral("m_tomorrow_weather_logo_lbl"));
    m_tomorrow_weather_logo_lbl->setFixedSize(60,50);


    m_tomorrow_weather_v_layout->addWidget(m_tomorrow_weather_logo_lbl);


    m_bottom_h_layout->addLayout(m_tomorrow_weather_v_layout);

    //后天
    m_after_tomorrow_weather_v_layout = new QVBoxLayout();
    m_after_tomorrow_weather_v_layout->setSpacing(6);
    m_after_tomorrow_weather_v_layout->setObjectName(QStringLiteral("m_after_tomorrow_weather_v_layout"));
    label_10 = new QLabel();
    label_10->setObjectName(QStringLiteral("label_10"));
    label_10->setAlignment(Qt::AlignHCenter);//文字显示在中间


    m_after_tomorrow_weather_v_layout->addWidget(label_10);

    horizontalLayout_5 = new QHBoxLayout();
    horizontalLayout_5->setSpacing(6);
    horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
    m_after_tomorrow_mini_temperature_lbl = new QLabel();
    m_after_tomorrow_mini_temperature_lbl->setObjectName(QStringLiteral("m_after_tomorrow_mini_temperature_lbl"));

    horizontalLayout_5->addWidget(m_after_tomorrow_mini_temperature_lbl);


    m_after_tomorrow_weather_v_layout->addLayout(horizontalLayout_5);

    m_after_tomorrow_weather_logo_lbl = new QLabel();
    m_after_tomorrow_weather_logo_lbl->setObjectName(QStringLiteral("m_after_tomorrow_weather_logo_lbl"));
    m_after_tomorrow_weather_logo_lbl->setFixedSize(60,50);

    m_after_tomorrow_weather_v_layout->addWidget(m_after_tomorrow_weather_logo_lbl);


    m_bottom_h_layout->addLayout(m_after_tomorrow_weather_v_layout);
    m_bottom_h_layout->addStretch(0);
}

void WeatherInfoFloatingWidget::retranslateUi()
{
 //   this->setStyleSheet(QStringLiteral("QWidget{background-color:red;}"));


    m_cur_temperature_lbl->setText( "35\342\204\203");
    m_cur_location_lbl->setText( "\351\207\215\345\272\206");
    m_meteorology_lbl->setText( "\345\244\232\344\272\221");
    m_wind_lbl->setText( "\344\270\234\345\215\227\351\243\216");
//    m_air_qulity_lbl->setText( "\347\251\272\346\260\224\350\264\250\351\207\217\344\274\230"); //空气质量暂时不用
//    label_6->setText( "pm2.5");
//    m_pm25_lbl->setText( "50");//pm2.5暂时不用
    label_8->setText( "\344\273\212\345\244\251");
    m_cur_mini_temperature_lbl->setText( "35\342\204\203");

//    label_12->setText( "/");
//    m_cur_max_temperature_lbl->setText( "38\342\204\203");

    m_cur_weather_logo_lbl->setText( "TextLabel");
    label_9->setText( "\346\230\216\345\244\251");
    m_tomorrow_mini_temperature_lbl->setText( "35\342\204\203");

//    label_15->setText( "/");
//    m_tomorrow_max_temperature_lbl->setText( "38\342\204\203");

    m_tomorrow_weather_logo_lbl->setText( "TextLabel");
    label_10->setText( "\345\220\216\345\244\251");
    m_after_tomorrow_mini_temperature_lbl->setText( "35\342\204\203");

//    label_18->setText( "/");
//    m_after_tomorrow_max_temperature_lbl->setText( "38\342\204\203");

    m_after_tomorrow_weather_logo_lbl->setText( "TextLabel");
}

void WeatherInfoFloatingWidget::enterEvent(QEvent *event)
{
    if(m_widget_showing_timer->isActive())
    {
        m_widget_showing_timer->stop();
    }

    DraggableWidget::enterEvent(event);
}

void WeatherInfoFloatingWidget::leaveEvent(QEvent *event)
{
    onHideWeatherInfoFloatingWidget();
    DraggableWidget::leaveEvent(event);
}

void WeatherInfoFloatingWidget::showEvent(QShowEvent *event)
{
    if(m_widget_showing_timer->isActive())
    {
        m_widget_showing_timer->stop();
    }

    DraggableWidget::showEvent(event);
}

void WeatherInfoFloatingWidget::onHideWeatherInfoFloatingWidget()
{
    if(!m_widget_showing_timer->isActive())
    {
        m_widget_showing_timer->start(1000);
    }

}


void WeatherInfoFloatingWidget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
}


//把插件加载函数包装至本地
template<class T>
bool WeatherInfoFloatingWidget::on_load_plugin(T &interface)
{
    return Baijuhua::Utils::SettingsUtils::load_plugin(interface);
}

QString WeatherInfoFloatingWidget::on_get_ip_local_addr()
{
    if(m_network_info_plugin == NULL){
        on_load_plugin(m_network_info_plugin);
    }

    QList<QString> lst_ip_addr;
    QString ip_local_addr;

    lst_ip_addr = m_network_info_plugin->to_get_valid_host_ip_address();
    QListIterator<QString> i(lst_ip_addr);
    while (i.hasNext()) {
        if(i.next() != "" || i.next() != NULL)
        {
            ip_local_addr = i.next();
        }
    }

    return ip_local_addr;
}

QString WeatherInfoFloatingWidget::on_get_ip_internet_addr()
{
    if(m_network_info_plugin == NULL){
        on_load_plugin(m_network_info_plugin);
    }

    QString ip_addr = m_network_info_plugin->to_get_valid_host_internet_ip_address();

    return ip_addr;

//    if (m_network_access_manager == NULL){
//        m_network_access_manager = new QNetworkAccessManager(this);
//    }
//    m_network_reply = m_network_access_manager->get(QNetworkRequest(QUrl(LOGINIPINTER)));

//    QByteArray response_data;
//    QEventLoop event_loop;
//    QObject::connect(m_network_access_manager,SIGNAL(finished(QNetworkReply *)), &event_loop, SLOT(quit()));
//    event_loop.exec(QEventLoop::ExcludeUserInputEvents);//事件循环，要除键盘和鼠标事件
//    response_data = m_network_reply->readAll();

//    if(event_loop.isRunning())
//    {
//        event_loop.exit(0);
//    }

//    QString str_ip = QString(response_data);
//    m_network_reply->deleteLater();
//    qDebug()<<"Internet IP Addr:"<<str_ip;


//    return str_ip;

}

////根据互联网出口IP判断地理位置，但包含了运营商
QString WeatherInfoFloatingWidget::on_get_location_addr_by_internet_ip()
{
    if(m_network_info_plugin == NULL){
        on_load_plugin(m_network_info_plugin);
    }

    QString str_location_addr = m_network_info_plugin->to_get_valid_location_by_host_internet_ip_addr_with_sina();

    return str_location_addr.split(QStringLiteral("	")).at(5);//返回去除运营商后的纯地址
}

void WeatherInfoFloatingWidget::on_load_city_keys()
{
    QFile file(":/resources/data/citykeys.txt");
    if ( !file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        return ;

    }

    QString tmp;
    while (file.atEnd() == 0) {
        tmp = file.readAll();
    }

    QStringList list = tmp.split(",");
    for(int i = 0; i < list.length(); i++) {
        QString s = list.at(i);
        QString citys = s.split(":").at(1);
        QString city = citys.replace("\"", "");
        QString codes = s.split(":").at(0);
        QString code = codes.replace("\"", "");
        citykeys.insert(city, code);
    }
}

QString WeatherInfoFloatingWidget::to_parse_city_key(QString city)
{
    if(citykeys[city]=="")
    {
        qDebug()<<QStringLiteral("Failed to find city code.");
        return NULL;
    }
   return citykeys[city];
}

QString WeatherInfoFloatingWidget::to_get_weather_report(QString city_key)
{
    if (m_network_access_manager == NULL){
        m_network_access_manager = new QNetworkAccessManager(this);
    }
    m_network_reply = m_network_access_manager->get(QNetworkRequest(QUrl(WEATHER_FORCAST_URL_TODAY + city_key)));

    QByteArray response_data;
    QEventLoop event_loop;
    QObject::connect(m_network_access_manager,SIGNAL(finished(QNetworkReply *)), &event_loop, SLOT(quit()));
    event_loop.exec(QEventLoop::ExcludeUserInputEvents);//事件循环，要除键盘和鼠标事件
    response_data = m_network_reply->readAll();

    if(event_loop.isRunning())
    {
        event_loop.exit(0);
    }

    QString str_json_or_xml = response_data.data();
    m_network_reply->deleteLater();
    qDebug()<<"Get weather forecast data:"<<str_json_or_xml;

    return str_json_or_xml.trimmed();
}

QString WeatherInfoFloatingWidget::to_get_forecast_weather_report(QString city_key)
{
    if (m_network_access_manager == NULL){
        m_network_access_manager = new QNetworkAccessManager(this);
    }
    m_network_reply = m_network_access_manager->get(QNetworkRequest(QUrl(WEATHER_FORCAST_URL + city_key)));

    QByteArray response_data;
    QEventLoop event_loop;
    QObject::connect(m_network_access_manager,SIGNAL(finished(QNetworkReply *)), &event_loop, SLOT(quit()));
    event_loop.exec(QEventLoop::ExcludeUserInputEvents);//事件循环，要除键盘和鼠标事件
    response_data = m_network_reply->readAll();

    if(event_loop.isRunning())
    {
        event_loop.exit(0);
    }

    QString str_json_or_xml = response_data.data();
    m_network_reply->deleteLater();
    qDebug()<<"Get weather forecast data:"<<str_json_or_xml;

    return str_json_or_xml.trimmed();
}

void WeatherInfoFloatingWidget::to_parse_this_day_weather_report_by_xml(QString server_data)
{
    QXmlStreamReader xml(server_data);

      while(!xml.atEnd())
      {
          if(xml.hasError())
          {
              QMessageBox::information(this,tr("出错啦"),tr("数据出错,请重试"),QMessageBox::Ok,QMessageBox::Ok);
              return;
          }
          else if(xml.isStartElement())
          {
              if(xml.name()=="city")
              {
                  m_weather_today.city = xml.readElementText();
              }
              else if(xml.name()=="updatetime")
              {
                  m_weather_today.updatetime = xml.readElementText();
              }
              else if(xml.name()=="wendu")
              {
                  m_weather_today.wendu = xml.readElementText();
              }
              else if(xml.name()=="fengli")
              {
                  m_weather_today.fengli = xml.readElementText();
              }
              else if(xml.name()=="shidu")
              {
                  m_weather_today.shidu = xml.readElementText();
              }
              else if(xml.name()=="fengxiang")
              {
                  m_weather_today.fengxiang = xml.readElementText();
              }
              else if(xml.name()=="sunrise_1")
              {
                  m_weather_today.sunrise = xml.readElementText();
              }
              else if(xml.name()=="sunset_1")
              {
                  m_weather_today.sunset = xml.readElementText();
                  xml.clear();
//                  m_cur_temperature_lbl->setText(tr("%1℃").arg(m_weather_today.wendu));
//                  m_cur_location_lbl->setText(m_weather_today.city);
//                  //m_meteorology_lbl->setText(m_weather_today.);
//                  m_wind_lbl->setText(m_weather_today.fengxiang);

                  return;
              }
              else
                  xml.readNext();
          }
          else
              xml.readNext();
      }
      xml.clear();
}

void WeatherInfoFloatingWidget::to_parse_forecast_weather_report_by_json(QString server_data)
{
    QByteArray byte_array;
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(byte_array.append(server_data),&json_error);

    if(json_error.error == QJsonParseError::NoError)
    {
        QJsonObject obj = parse_doucment.object();

        QJsonValue desc = obj.take("desc");
        if(desc.toString() != "OK")
        {
            //qDebug()<<"城市错误\n";
            QMessageBox::information(this,tr("抱歉"),tr("暂无此城市的天气情况"),QMessageBox::Ok,QMessageBox::Ok);
            return;
        }

        QJsonValue data = obj.take("data");
        m_weather_today.ganmao = data.toObject().take("ganmao").toString();
        QJsonValue forecast1 = data.toObject().take("forecast");
        QJsonArray forecast2 = forecast1.toArray();
        for(int i=0; i<3; i++)
        {
            QJsonValue value = forecast2.at(i);
            QJsonObject object = value.toObject();
            m_weather_forecast[i].fengxiang = object.take("fengxiang").toString();
            m_weather_forecast[i].date = object.take("date").toString();
            m_weather_forecast[i].fengli = object.take("fengli").toString();
            m_weather_forecast[i].high = object.take("high").toString();
            m_weather_forecast[i].low = object.take("low").toString();
            m_weather_forecast[i].type = object.take("type").toString();
        }

//        for(int i=0;i<3;i++)
//        {
//            //m_weather_forecast_date_list[i]->setText(tr("%1").arg(m_weather_forecast[i].date));
//            m_weather_forecast_temp_list[i]->setText(tr("%1/%2").arg(m_weather_forecast[i].low.split(" ").at(1)).arg(m_weather_forecast[i].high.split(" ").at(1)));
//            m_weather_forecast_type_list[i]->setPixmap(QPixmap(tr(":/resources/default/weather_skin/old_res/%1.png").arg(m_weather_forecast[i].type)).scaled(60,50,Qt::KeepAspectRatioByExpanding));
//            m_weather_forecast_type_list[i]->setToolTip(tr("%1 : %2/%3").arg(m_weather_forecast[i].type).arg(m_weather_forecast[i].fengli).arg(m_weather_forecast[i].fengxiang));
//        }
//        m_meteorology_lbl->setText(m_weather_forecast[0].type);
//        ui->forecast_0_date->setText(tr("今天"));

    }
    else
    {
        qDebug()<<QStringLiteral("Json错误");
        QMessageBox::information(this,tr("出错啦"),tr("数据出错,请重试"),QMessageBox::Ok,QMessageBox::Ok);
        return;
    }
}

void WeatherInfoFloatingWidget::onSetFlashLoadFinished(bool is_finished)
{
    m_is_flash_load_finished = is_finished;
//    m_p_weather_flash_web_engine_page->setBackgroundColor(QColor(255,255,255,255));
//    if(is_finished == true)
//    {
//        QSize size =  m_p_weather_flash_web_engine_view->page()->contentsSize().toSize();
//        m_p_weather_flash_web_engine_view->setMaximumWidth(m_p_weather_flash_web_engine_view->width()*size.width()/m_p_weather_flash_web_engine_view->width());
//    }

}
