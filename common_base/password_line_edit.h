/*!
  *@file
  *@brief   为密码输入框添加密码图标，以便点击密码图标弹出虚拟键盘
  *@author  Tzaihua
  *@date    2017-02-02
  */

#ifndef PASSWORD_LINE_EDIT_H
#define PASSWORD_LINE_EDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>

class PasswordLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    PasswordLineEdit(QWidget *parent = 0);
protected:
    QPushButton *m_keyboard_btn;//键盘图标按钮
    QHBoxLayout *m_main_h_layout;//密码输入框的整体横向布局
signals:
    void showVirtualKeyboard();
    void virtualKeyboardClicked();//虚拟键盘按钮被点击的信号
public slots:
    void onShowVirtualKeyboard();//显示虚拟键盘
    void onHideVirtualKeyboard();//隐藏虚拟键盘

};

#endif // PASSWORD_LINE_EDIT_H
