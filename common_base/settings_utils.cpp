#include "settings_utils.h"


namespace Baijuhua{
namespace Utils{

SettingsUtils::SettingsUtils()
{

}


QString SettingsUtils::get_app_dir_path()
{
    return QApplication::applicationDirPath();
}

bool SettingsUtils::save_data_to_ini_file(QString path, QString group, QString user_key, QString user_value)
{
    if(path.isEmpty() || group.isEmpty() || user_key.isEmpty() )
    {
        return false;
    }
    else
    {
        //创建配置文件操作对象
        QSettings *config = new QSettings(path, QSettings::IniFormat);

        //将信息写入配置文件
        config->beginGroup(group);
        config->setValue(user_key, user_value);
        config->endGroup();

        return true;
    }
}

bool SettingsUtils::read_data_from_ini_file(QString path, QString group, QString user_key, QString &user_value)
{
    user_value = QString("");

    if(path.isEmpty() || group.isEmpty() || user_key.isEmpty() )
    {
        return false;
    }
    else
    {
        //创建配置文件操作对象
        QSettings *config = new QSettings(path, QSettings::IniFormat);

        //读取用户配置信息
        user_value = config->value(QString(group+"/") + user_key).toString();

        return true;
    }

}

bool SettingsUtils::save_config_data_to_ini_file(QString file_name, QString group, QString user_key, QString user_value)
{
    if(file_name.isEmpty() || group.isEmpty() || user_key.isEmpty() )
    {
        return false;
    }else
    {
        QString app_path = get_app_dir_path();
        QString config_file_full_path = app_path + "/" +Baijuhua::APP_CONFIG_DIR+ "/" + file_name +".ini";

        save_data_to_ini_file(config_file_full_path,group,user_key,user_value);

        return true;
    }


}



}//namespace Utils

}//namespace InstantAssistantToolKits
