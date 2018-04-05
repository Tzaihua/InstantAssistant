/*!
  *@file
  *@brief   模拟TabWidget中的TabBar按钮
  *@author  Tzaihua
  *@date    2016-12-22
  */

#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QObject>
#include <QWidget>
#include <QToolButton>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QIcon>
#include <QMessageBox>

class ToolButton : public QToolButton
{
    Q_OBJECT
public:

    explicit ToolButton(QWidget *parent = 0);
    ~ToolButton();

    Q_PROPERTY(QPixmap normal_pixmap READ get_normal_pixmap WRITE set_normal_pixmap)

    Q_PROPERTY(QPixmap active_pixmap READ get_active_pixmap WRITE set_active_pixmap)

    Q_PROPERTY(QPixmap selected_pixmap READ get_selected_pixmap WRITE set_selected_pixmap)

    Q_PROPERTY(QPixmap disabled_pixmap READ get_disabled_pixmap WRITE set_disabled_pixmap)

    Q_PROPERTY(QPixmap hover_pixmap READ get_normal_pixmap WRITE set_hover_pixmap)

    Q_PROPERTY(QPixmap pressed_pixmap READ get_pressed_pixmap WRITE set_pressed_pixmap)

    Q_PROPERTY(QPixmap checked_pixmap READ get_checked_pixmap WRITE set_checked_pixmap)

    Q_PROPERTY(QPixmap focus_pixmap READ get_focus_pixmap WRITE set_focus_pixmap)


    void setMousePress(bool mouse_press);

    //设置按钮Normal状态ICON
    void set_normal_pixmap(QPixmap pixmap);
    QPixmap get_normal_pixmap();

    //设置按钮Active状态ICON
    void set_active_pixmap(QPixmap pixmap);
    QPixmap get_active_pixmap();

    //设置按钮Selected状态ICON
    void set_selected_pixmap(QPixmap pixmap);
    QPixmap get_selected_pixmap();

    //设置按钮Disabled状态ICON
    void set_disabled_pixmap(QPixmap pixmap);
    QPixmap get_disabled_pixmap();

    //设置按钮Hover状态ICON
    void set_hover_pixmap(QPixmap pixmap);
    QPixmap get_hover_pixmap();

    //设置按钮Pressed状态ICON
    void set_pressed_pixmap(QPixmap pixmap);
    QPixmap get_pressed_pixmap();

    //设置按钮Checked状态ICON
    void set_checked_pixmap(QPixmap pixmap);
    QPixmap get_checked_pixmap();

    //设置按钮Focus状态ICON
    void set_focus_pixmap(QPixmap pixmap);
    QPixmap get_focus_pixmap();

private:
    //QIcon原生状态
    QPixmap m_normal_pixmap;
    QPixmap m_active_pixmap;
    QPixmap m_selected_pixmap;
    QPixmap m_disabled_pixmap;
    //CSS中有的状态
    QPixmap m_hover_pixmap;
    QPixmap m_pressed_pixmap;
    QPixmap m_checked_pixmap;
    QPixmap m_focus_pixmap;

protected:
    void paintEvent(QPaintEvent *event);
    void paint_info(QPixmap pixmap);

};

#endif // TOOLBUTTON_H
