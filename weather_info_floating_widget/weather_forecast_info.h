#ifndef WEATHER_FORECAST_INFO_H
#define WEATHER_FORECAST_INFO_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QList>
#include <QXmlStreamReader>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include <QtWidgets/QWidget>
#include <QMessageBox>
//插件
#include <QPluginLoader>
#include "global_constant.h"
#include "settings_utils.h"
#include "network_info_plugin_interface.h"      //网络工具插件


const QString WEATHER_FORCAST_URL = "http://wthrcdn.etouch.cn/weather_mini?citykey=";//用于提取预测的天气，这个URL所获取的信息不全
const QString WEATHER_FORCAST_URL_TODAY = "http://wthrcdn.etouch.cn/WeatherApi?citykey=";//用于提取今天天气

struct WeatherForecast
{
    QString fengxiang;
    QString fengli;
    QString high;
    QString type;
    QString low;
    QString date;
};

struct WeatherToday
{
    QString ganmao;
    QString city;
    QString updatetime;
    QString wendu;
    QString fengli;
    QString fengxiang;
    QString sunrise;
    QString sunset;
    QString shidu;
};

class WeatherForecastInfo : public QObject
{
    Q_OBJECT
public:
    explicit WeatherForecastInfo(QObject *parent = nullptr);
    ~WeatherForecastInfo();
    //今日天气
    Q_PROPERTY(WeatherToday weather_today READ get_weather_today)
    //后几日天气预报
    Q_PROPERTY(QList<WeatherForecast> weather_forecast READ get_weather_forecast)

    WeatherToday get_weather_today() const;
    QList<WeatherForecast> get_weather_forecast() const;

signals:

public slots:

private:
    //插件
    NetworkInfoPluginInterface *m_network_info_plugin;

    QString m_ip_local_addr;           //本地IP地址
//     QString m_ip_internet_addr;        //本机在互联网上的IP地址

    QList<QString> m_lst_ip_addr;
    //插件加载函数
    template<class T>
    bool on_load_plugin(T &interface);

    //获取本地IP地址
    QString on_get_ip_local_addr();
    //获取互联网出口IP地址
    QString on_get_ip_internet_addr();
    //获取地理位置信息
    QString on_get_location_addr_by_internet_ip();

    QNetworkReply		 *m_network_reply;
    QNetworkAccessManager *m_network_access_manager;

    WeatherForecast m_weather_forecast[3];
    WeatherToday m_weather_today;


    QMap<QString,QString> citykeys;//存储城市代码

    void on_load_city_keys();//加载城市代码文件
    QString to_parse_city_key(QString city);//根据城市名称解析出城市代码

    QString to_get_weather_report(QString city_key);//获取天气预报
    QString to_get_forecast_weather_report(QString city_key);//获取天气预报

    void to_parse_this_day_weather_report_by_xml(QString server_data);
    void to_parse_forecast_weather_report_by_json(QString server_data);

};

#endif // WEATHER_FORECAST_INFO_H
