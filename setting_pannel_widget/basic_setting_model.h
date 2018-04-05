#ifndef BASIC_SETTING_MODEL_H
#define BASIC_SETTING_MODEL_H

#include <QObject>

class BasicSettingModel:public QObject
{
    Q_OBJECT
public:
    explicit BasicSettingModel();

//    Q_PROPERTY(bool is_auto_start READ get_normal_pixmap WRITE set_normal_pixmap)


private:
    bool m_auto_start;//开机时自动启动程序
    bool m_open_login_prompt;//总是打开登录提示
    bool m_subscribe_to_daily_info;//订阅每日资讯

public:
    bool is_auto_start();
    bool is_open_login_prompt();
    bool is_subscribe_to_daily_info();
};

#endif // BASIC_SETTING_MODEL_H
