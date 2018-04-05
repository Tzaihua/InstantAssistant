#ifndef INSTANT_MESSAGE_DIALOG_H
#define INSTANT_MESSAGE_DIALOG_H

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QTimer>
#include "global_constant.h"
#include "draggable_widget.h"
#include "dialog_title_widget.h"

#include <QSysInfo>
#include <QOperatingSystemVersion>

class InstantMessageDialog : public DraggableWidget
{
    Q_OBJECT
public:
    explicit InstantMessageDialog(QWidget *parent = 0);

    ~InstantMessageDialog();
    void setupUi();
    void retranslateUi();

private:
    DialogTitleWidget *m_dialog_title_widget;//对话框顶部标题部分
    QVBoxLayout *m_main_v_layout;//整体垂直布局
    QLabel *m_content_label;//内容

    QTimer *m_timer_show;//开始
    QTimer *m_timer_stay;//保持
    QTimer *m_timer_close;//关闭

    int m_desktop_height;//桌面高度
    int m_desktop_width;//桌面宽度
    QPoint normal_point;
    //QRect desktop_rect;

    int m_time_count;
    double m_transparent;


signals:

public slots:
    void onShowMinimize();//最小化窗体
    void onCloseWidget();//关闭窗体

    void onShowMessage(QString title, QString content);

    void onMove();
    void onStay();
    void onClose();

private:
    void showMessage();

};

#endif // INSTANT_MESSAGE_DIALOG_H
