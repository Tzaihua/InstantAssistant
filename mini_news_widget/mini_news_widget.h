#ifndef MINI_NEWS_WIDGET_H
#define MINI_NEWS_WIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QEventLoop>
#include <QTimer>
#include <QtWebEngineWidgets>

#include "global_constant.h"
#include "draggable_widget.h"
#include "dialog_title_widget.h"

using namespace Baijuhua;

class MiniNewsWidget : public DraggableWidget
{
    Q_OBJECT
public:
    explicit MiniNewsWidget(QWidget *parent = 0);
    ~MiniNewsWidget();
    void setupUi();
    void retranslateUi();

protected:
    virtual void showEvent(QShowEvent *event);

private:
    DialogTitleWidget *m_dialog_title_widget;//对话框顶部标题部分
    QVBoxLayout *m_main_v_layout;//整体垂直布局
    QWebEngineView *m_web_engine_view;
signals:

public slots:
    void onShowMinimize();//最小化窗体
    void onCloseWidget();//关闭窗体
    void onGradientShow();//渐变显示
private:
    QTimer *m_timer_show;//开始
    double m_transparent = 0.0;//窗体透明度

};

#endif // MINI_NEWS_WIDGET_H
