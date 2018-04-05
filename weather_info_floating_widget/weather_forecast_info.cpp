#include "weather_forecast_info.h"

WeatherForecastInfo::WeatherForecastInfo(QObject *parent) : QObject(parent)
{
    m_network_access_manager = NULL;
    m_network_reply = NULL;

    if(!on_load_plugin(m_network_info_plugin))
    {
        //如果无法加载插件
         qDebug()<<QStringLiteral("Could not load the NetworkInfoPluginInterface plugin.");
         //QMessageBox::information(this,"Error","网络插件加载失败！");

    }else{
        qDebug()<<QStringLiteral("load the NetworkInfoPluginInterface plugin successful.");
    }

    on_load_city_keys();
    QString str_city_key =  to_parse_city_key(on_get_location_addr_by_internet_ip());
    to_parse_this_day_weather_report_by_xml(to_get_weather_report(str_city_key));

    to_parse_forecast_weather_report_by_json(to_get_forecast_weather_report(str_city_key));

}

WeatherForecastInfo::~WeatherForecastInfo()
{
    if(m_network_access_manager)
    {
        delete m_network_access_manager;
    }
    m_network_access_manager = NULL;

    if(m_network_reply)
    {
        delete m_network_reply;
    }
    m_network_reply = NULL;

}

//把插件加载函数包装至本地
template<class T>
bool WeatherForecastInfo::on_load_plugin(T &interface)
{
    return Baijuhua::Utils::SettingsUtils::load_plugin(interface);
}

QString WeatherForecastInfo::on_get_ip_local_addr()
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

QString WeatherForecastInfo::on_get_ip_internet_addr()
{
    if(m_network_info_plugin == NULL){
        on_load_plugin(m_network_info_plugin);
    }

    QString ip_addr = m_network_info_plugin->to_get_valid_host_internet_ip_address();

    return ip_addr;

}

////根据互联网出口IP判断地理位置，但包含了运营商
QString WeatherForecastInfo::on_get_location_addr_by_internet_ip()
{
    if(m_network_info_plugin == NULL){
        on_load_plugin(m_network_info_plugin);
    }

    QString str_location_addr = m_network_info_plugin->to_get_valid_location_by_host_internet_ip_addr_with_sina();

    return str_location_addr.split(QStringLiteral("	")).at(5);//返回去除运营商后的纯地址
}

void WeatherForecastInfo::on_load_city_keys()
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

QString WeatherForecastInfo::to_parse_city_key(QString city)
{
    if(citykeys[city]=="")
    {
        qDebug()<<QStringLiteral("Failed to find city code.");
        return NULL;
    }
   return citykeys[city];
}

QString WeatherForecastInfo::to_get_weather_report(QString city_key)
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

QString WeatherForecastInfo::to_get_forecast_weather_report(QString city_key)
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

void WeatherForecastInfo::to_parse_this_day_weather_report_by_xml(QString server_data)
{
    QXmlStreamReader xml(server_data);

      while(!xml.atEnd())
      {
          if(xml.hasError())
          {
              //QMessageBox::information(this,tr("出错啦"),tr("数据出错,请重试"),QMessageBox::Ok,QMessageBox::Ok);
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

void WeatherForecastInfo::to_parse_forecast_weather_report_by_json(QString server_data)
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
            //QMessageBox::information(this,tr("抱歉"),tr("暂无此城市的天气情况"),QMessageBox::Ok,QMessageBox::Ok);
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

    }
    else
    {
        qDebug()<<QStringLiteral("Json错误");
        //QMessageBox::information(this,tr("出错啦"),tr("数据出错,请重试"),QMessageBox::Ok,QMessageBox::Ok);
        return;
    }
}

WeatherToday WeatherForecastInfo::get_weather_today() const
{
    return m_weather_today;
}

QList<WeatherForecast> WeatherForecastInfo::get_weather_forecast() const
{
     QList<WeatherForecast> *forcast = new QList<WeatherForecast>();
     for(int i=0;i<3;i++)
     {
         forcast->append(m_weather_forecast[i]);
     }
     return *forcast;
}
