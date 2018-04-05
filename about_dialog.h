#ifndef ABOUT_DIALOG_H
#define ABOUT_DIALOG_H

//UI
#include <QObject>
#include <QWidget>
#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QTextBrowser>
#include <QDesktopServices>
#include <QShowEvent>

#include "global_constant.h"
#include "draggable_widget.h"
#include "dialog_title_widget.h"
#include "clicked_label.h"

//数据
#include <QFile>
using namespace Baijuhua;

class AboutDialog : public DraggableWidget
{
    Q_OBJECT
public:
    explicit AboutDialog(QWidget *parent = 0);
    ~AboutDialog();
    void setupUi();
    void retranslateUi();

protected:
    //在显示的时候再去读license文件，如果文件大，在这儿读取就不合适了
    void showEvent(QShowEvent *event);

private:
    DialogTitleWidget *m_dialog_title_widget;//对话框顶部标题部分
    QVBoxLayout *m_main_v_layout;//整体垂直布局

    QLabel *m_app_pictorial;//软件关于界面的画报

    //对话框中间部分
    QWidget *m_center_widget;
    QVBoxLayout *m_center_v_layout;
    QLabel *m_app_name_lbl;
    QLabel *m_app_company_lbl;
    QLabel *m_copyright_lbl;
    QHBoxLayout *m_center_h_layout;
    QPushButton *m_official_website_btn;//官网
    QPushButton *m_user_agreement_btn;//用户协议
//    ClickedLabel *m_website_lbl;
//    ClickedLabel *m_user_agreement_lbl;
    QTextBrowser *m_other_statements_tb;

    QWidget *m_bottom_main_widget;//对话框底部部件
    QHBoxLayout *m_bottom_h_layout;
    QPushButton *m_ok_btn;

private:
    void init_center_widget();

signals:

public slots:
    void onShowMinimize();//最小化窗体
    void onCloseWidget();//关闭窗体

    void onOpenWebsite();
    void onOpenUserAgreement();

private:
    void read_license();
};

#endif // ABOUT_DIALOG_H
