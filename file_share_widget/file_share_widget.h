#ifndef FILESHAREWIDGET_H
#define FILESHAREWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>
#include <QStackedWidget>
#include "global_constant.h"
#include "draggable_widget.h"
#include "dialog_title_widget.h"

class FileShareWidget  : public DraggableWidget
{
    Q_OBJECT
public:
    explicit FileShareWidget(QWidget *parent = 0);
    ~FileShareWidget();
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

#endif // FILESHAREWIDGET_H
