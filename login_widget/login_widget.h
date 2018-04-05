#ifndef LOGIN_WIDGET_H
#define LOGIN_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QDesktopServices>
#include <QSettings>
#include <QKeyEvent>
#include <QShortcut>
#include <QRegExp>
#include <QRegExpValidator>
#include <QEventLoop>
#include <QTimer>

#include "global_constant.h"
#include "draggable_widget.h"
#include "title_widget.h"
//#include "main_widget.h"
#include "password_line_edit.h"

#include "error_message_widget.h"

#include "settings_utils.h"  //工具类


using namespace Baijuhua;
using namespace Utils;

class LoginWidget : public DraggableWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();
    void setupUi();
    void retranslateUi();

protected:
    void keyPressEvent(QKeyEvent * event);
    void closeEvent(QCloseEvent *event);//关闭对话框时要做的事情


private:
    QVBoxLayout *m_main_fame_v_layout;//主窗体垂直布局
    QWidget *m_top_widget;//项部部件，用于将标题、用户信息部件纳入；
    TitleWidget *m_title_widget;//窗体顶部标题部件
    QWidget *m_msg_widget;//错误消息点位部件

    QWidget *m_center_widget;//中间部件

    QLabel *m_app_pictorial;//软件登录界面的画报
    QVBoxLayout *m_center_v_layout;
    QHBoxLayout *m_center_h_layout;//用于记住密码与自动登录处布局
    QLineEdit *m_user_name_le;//用户输入框
    //QLineEdit *m_password_le;//密码输入框
    PasswordLineEdit *m_password_le;
    QCheckBox *m_is_remember_password;//记住密码
    QCheckBox *m_is_auto_login;//自动登录
    QPushButton *m_submit_btn;//登录按钮

    ErrorMessageWidget *m_err_msg_widget;//错误消息显示框


    QWidget *m_bottom_widget;//底部界面
    QVBoxLayout *m_bottom_v_layout;//底部布局
    QPushButton *m_register_account_btn;//注册帐户按钮
    QPushButton *m_retrieve_password_btn;//找回密码按钮
    QPushButton *m_network_setting_btn;//网络设置

private:
    void init_top_widget();// 初始化顶部部件
    void init_center_widget();//初始化中间部件
    void init_bottom_widget();//初始化底部部件

    bool save_widget_position();//记录窗体坐标信息
    bool save_current_user_operate_system_info();//保存当前用户系统信息

signals:


public slots:
    void onRegisterAccount();
    void onRetrievePassword();

    void onUserNameLineEditValueChanged(const QString &str);

    //是否记住密码QCheckBox控件状态改变
    void onIsRememberPasswordValueChanged(int i);
    //是否自动登录QCheckBox控件状态改变
    void onIsAutoLoginValueChanged(int i);

    //提交登录申请
    bool onCommitLogin();

    void onHideErrorMessageWidget();

    void onLoginAccepted();//向主窗体返回登录状态
    void onLoginRejected();//向主窗体返回登录状态


    //数据
private:
    QString m_str_user_name;
    QString m_str_password;

    bool m_is_login;

    void initialize();//初始化数据
    void validate();//控件限制性输入

};

#endif // LOGIN_WIDGET_H
