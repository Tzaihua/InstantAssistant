#ifndef COLLECTION_WIDGET_H
#define COLLECTION_WIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include "global_constant.h"
#include "draggable_widget.h"
#include "dialog_title_widget.h"

class CollectionWidget : public DraggableWidget
{
    Q_OBJECT
public:
    explicit CollectionWidget(QWidget *parent = 0);
    ~CollectionWidget();
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

#endif // COLLECTION_WIDGET_H
