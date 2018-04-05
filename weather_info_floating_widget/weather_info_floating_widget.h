#ifndef WEATHER_INFO_FLOATING_WIDGET_H
#define WEATHER_INFO_FLOATING_WIDGET_H

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QStackedLayout>
#include <QtWidgets/QStackedWidget>

#include <QtWebEngineWidgets>
#include <QWebEngineView>

#include <QEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QTimerEvent>
#include <QMessageBox>
#include <QList>
#include <QXmlStreamReader>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "draggable_widget.h"
#include "global_constant.h"

//插件
#include <QPluginLoader>
#include "global_constant.h"
#include "settings_utils.h"
#include "network_info_plugin_interface.h"      //网络工具插件

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "weather_forecast_info.h"

using namespace Baijuhua;


//const QString WEATHER_FORCAST_URL = "http://wthrcdn.etouch.cn/weather_mini?citykey=";//用于提取预测的天气，这个URL所获取的信息不全
//const QString WEATHER_FORCAST_URL_TODAY = "http://wthrcdn.etouch.cn/WeatherApi?citykey=";//用于提取今天天气

//struct WeatherForecast
//{
//    QString fengxiang;
//    QString fengli;
//    QString high;
//    QString type;
//    QString low;
//    QString date;
//};

//struct WeatherToday
//{
//    QString ganmao;
//    QString city;
//    QString updatetime;
//    QString wendu;
//    QString fengli;
//    QString fengxiang;
//    QString sunrise;
//    QString sunset;
//    QString shidu;
//};


class WeatherInfoFloatingWidget : public DraggableWidget //QWidget
{
    Q_OBJECT
public:
    explicit WeatherInfoFloatingWidget(QWidget *parent = nullptr);
    ~WeatherInfoFloatingWidget();
    void setupUi();
    void retranslateUi();

protected:
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void showEvent(QShowEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);//基类在鼠标按住的情况下，可拖地，现将其屏蔽掉

public:

    QStackedLayout *m_main_s_layout;        //层叠布局，用于将GIF动画显示与天气信息显示整合在一起

    QWebEngineView *m_p_weather_flash_web_engine_view;      //用于显示天气的FLASH

    QWidget *m_p_weather_info_widget;       //天气信息容器
    QWidget *m_p_weather_info_bottom_widget;//底部未来几天天气容器

    //------------天气信息容器布局组件
private:

     QVBoxLayout *m_main_v_layout;          //主布局,天气信息的主布局

     QVBoxLayout *m_p_up_v_layout;          //上端天气布局

     QHBoxLayout *m_top_h_layout;           //顶部温度布局
     QLabel *m_cur_temperature_lbl;         //当前温度
     QHBoxLayout *m_center_local_h_layout;  //当前地市区布局
     QLabel *m_cur_location_lbl;            //当前地市
     QHBoxLayout *m_center_wind_h_layout;   //中间气象风向布局
     QLabel *m_meteorology_lbl;             //气象，多云，阴天这些
     QLabel *m_wind_lbl;                    //风向
     QHBoxLayout *m_center_air_h_layout;    //中间空气质量布局
     QLabel *m_air_qulity_lbl;              //空气质量
     QLabel *label_6;
     QLabel *m_pm25_lbl;                    //pm2.5
     QHBoxLayout *m_bottom_h_layout;        //底部近几时温度布局，包含下面今日、明天、后天温度布局

     QVBoxLayout *m_cur_weather_v_layout;   //今日温度布局
     QLabel *label_8;
     QHBoxLayout *horizontalLayout_3;       //今日最低、最高温度布局
     QLabel *m_cur_mini_temperature_lbl;    //今日最低温度
     QLabel *m_cur_weather_logo_lbl;        //今日气象图标

     QVBoxLayout *m_tomorrow_weather_v_layout;//明天温度布局
     QLabel *label_9;
     QHBoxLayout *horizontalLayout_4;//明天最低、最高温度布局
     QLabel *m_tomorrow_mini_temperature_lbl;//明天最低温度
     QLabel *m_tomorrow_weather_logo_lbl;//明天气象图标

     QVBoxLayout *m_after_tomorrow_weather_v_layout;//后天温度布局
     QLabel *label_10;
     QHBoxLayout *horizontalLayout_5;//后天最低、最高温度布局
     QLabel *m_after_tomorrow_mini_temperature_lbl;//后天最低温度
     QLabel *m_after_tomorrow_weather_logo_lbl;//后天气象图标

public:
     QTimer *m_widget_showing_timer;//用于控制窗体的显示时间
     //插件
     NetworkInfoPluginInterface *m_network_info_plugin;

signals:

public slots:
     void onHideWeatherInfoFloatingWidget();
     void onSetFlashLoadFinished(bool is_finished);//通过关联浏览器，返回FLASH是否加载完毕

private:
     void init_weather_info_up_widget();//初始化天气信息组件
     void init_weather_info_bottom_widget();//初始化未来几天天气信息组件

private:
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

     QList<QLabel *> m_weather_forecast_date_list;
     QList<QLabel *> m_weather_forecast_temp_list;
     QList<QLabel *> m_weather_forecast_type_list;

     QMap<QString,QString> citykeys;//存储城市代码

     void on_load_city_keys();//加载城市代码文件
     QString to_parse_city_key(QString city);//根据城市名称解析出城市代码

     QString to_get_weather_report(QString city_key);//获取天气预报
     QString to_get_forecast_weather_report(QString city_key);//获取天气预报

     void to_parse_this_day_weather_report_by_xml(QString server_data);
     void to_parse_forecast_weather_report_by_json(QString server_data);


     bool m_is_flash_load_finished = false;


};

#endif // WEATHER_INFO_FLOATING_WIDGET_H
