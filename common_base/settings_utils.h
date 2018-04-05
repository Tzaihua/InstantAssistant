#ifndef SETTINGS_UTILS_H
#define SETTINGS_UTILS_H


#include <QObject>
#include <QSettings>
#include <QApplication>
#include <QDir>
#include <QtPlugin>
#include <QPluginLoader>
#include <QDebug>
#include "global_constant.h"

namespace Baijuhua {

namespace Utils {

const QString APP_CONFIG_INI_FILE = "app_settings";//软件设置
const QString APP_SYSTEM_CONFIG_INI_FILE = "app_system_settings";//软件系统设置
const QString APP_WIDGET_CONFIG_INI_FILE ="app_widget_settings";//软件窗体设置
const QString USER_CURR_OS_INFO_CONFIG_INI_FILE ="user_current_os_info";//主要用于保存当前用户操作系统信息

class SettingsUtils
{
public:
    SettingsUtils();
    //获取应用程序根目录
    static QString get_app_dir_path();//

    //将数据写入INI文件
    static bool save_data_to_ini_file(QString path,QString group, QString user_key, QString user_value);
    //从INI文件中读取数据
    static bool read_data_from_ini_file(QString path,QString group, QString user_key, QString &user_value);


    //将配置数据写入配置文件，配置文件名及路径已经确定，即程序根路径下的config文件夹
    static bool save_config_data_to_ini_file(QString file_name,QString group, QString user_key, QString user_value);
    //从INI文件中读取配置文件
    static bool read_config_data_to_ini_file(QString file_name,QString group, QString user_key, QString &user_value);

    //模板函数，载入插件
    template<class T>
    static bool load_plugin(T &interface){

        QString app_path = QApplication::applicationDirPath();
        QDir pluginsDir(app_path + "/" + Baijuhua::APP_PLUGINS_DIR);//plugins

        //遍历插件目录
        foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
            qDebug()<<fileName;
            QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
            QObject *plugin = pluginLoader.instance();
            if(plugin)
            {
               qDebug()<<"instance plugin";
                interface = qobject_cast<T>(plugin);
                if(interface)
                {
                   qDebug()<<"fint the plugin";
                    return true;
               }
            }
            qDebug()<<"isn't the plugin";
        }
        return false;
    }


};//class SettingsUtils

}//namespace Utils

}//namespace Baijuhua

#endif // SETTINGS_UTILS_H
