#ifndef UNREAD_MSG_BOX_WIDGET_H
#define UNREAD_MSG_BOX_WIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>

#include "draggable_widget.h"

#include "dialog_title_widget.h"

class UnreadMsgBoxWidget : public DraggableWidget
{
    Q_OBJECT
public:
    explicit UnreadMsgBoxWidget(QWidget *parent = 0);
    ~UnreadMsgBoxWidget();
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

#endif // UNREAD_MSG_BOX_WIDGET_H
