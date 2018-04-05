#ifndef ERROR_MESSAGE_WIDGET_H
#define ERROR_MESSAGE_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QToolButton>
#include <QPixmap>
#include <QStyle>
#include <QHBoxLayout>

#include "global_constant.h"



class ErrorMessageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ErrorMessageWidget(QWidget *parent = 0);
    ~ErrorMessageWidget();
    void setupUi();
    void retranslateUi();
    void setTipInfo(QString info);//设置提示信息
    void setTipIcon(QPixmap pixmap);//

    void showInfomation(QString info);//直接显示提示类信息
    void showWarning(QString info);//直接显示警告信息

protected:
    virtual void paintEvent(QPaintEvent *event);//定义为虚函数，其子类继承时，可以重写


private:
    QHBoxLayout *m_main_h_layout;//主布局
    QToolButton *m_close_btn;//关闭按钮
    QLabel *m_msg_label;//提示信息图片
    QLabel *m_ask_label;//提示文字信息

    int m_width=0;


signals:

public slots:
    bool closeWidget();

};

#endif // ERROR_MESSAGE_WIDGET_H
