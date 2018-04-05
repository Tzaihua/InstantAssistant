/*!
  *@file
  *@brief   应用管理器
  *@author  Tzaihua
  *@date    2016-12-26
  */

#ifndef APPMANAGERWIDGET_H
#define APPMANAGERWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include "global_constant.h"
#include "draggable_widget.h"
#include "dialog_title_widget.h"

class AppManagerWidget : public DraggableWidget
{
    Q_OBJECT
public:
    explicit AppManagerWidget(QWidget *parent = 0);
    ~AppManagerWidget();
    void setupUi();
    void retranslateUi();

private:
    DialogTitleWidget *m_dialog_title_widget;//对话框顶部标题部分
    QVBoxLayout *m_main_v_layout;//整体垂直布局
signals:

public slots:
    void onShowMinimize();//最小化窗体
    void onCloseWidget();//关闭窗体
};

#endif // APPMANAGERWIDGET_H
