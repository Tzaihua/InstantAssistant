///
/// Desc:DraggableWidget 应用程序所用窗体的基类(暂时没启用)
/// 主要实现了窗体的无边框设计与鼠标拖动改变位置
/// 参考资料：http://blog.csdn.net/aqtata/article/details/8902889
/// 缺陷：鼠标拖动改变大小时，窗体抖动
/// Author:Tzaihua
/// Date：2016年10月9日
/// Modify Date:
///

#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QDialog>
#include <QMouseEvent>
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QDesktopWidget>

#include "global_constant.h"

class DraggableWidget : public QDialog //QWidget
{
    Q_OBJECT
public:
    explicit DraggableWidget(QWidget *parent = 0);
    Q_PROPERTY(QColor PaintBackgroundColor READ getPaintBackgroundColor WRITE setPaintBackgroundColor NOTIFY PaintBackgroundColorChanged DESIGNABLE true)
    QColor getPaintBackgroundColor() const;
    void setPaintBackgroundColor(const QColor paint_background_color);
private:
    QColor m_paint_background_color = Qt::white;
    QPoint startPos;//窗体的起始位置
    QPoint clickPos;//窗体被鼠标拖动后的位置
    bool isLeftPressDown;  // 判断左键是否按下
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);//定义为虚函数，其子类继承时，可以重写

signals:
    void PaintBackgroundColorChanged(const QColor paint_background_color);

public slots:

};

#endif // BASEWIDGET_H
