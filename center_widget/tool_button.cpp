#include "tool_button.h"

ToolButton::ToolButton(QWidget *parent)
    :QToolButton(parent)
{

    this->setToolButtonStyle(Qt::ToolButtonIconOnly);
    this->setAutoRaise(true);
    this->setCheckable(true);
    this->setAutoExclusive(true);
    this->setChecked(false);
}

ToolButton::~ToolButton()
{

}


void ToolButton::paintEvent(QPaintEvent *event)
{
    //设置图标
    QPixmap pixmap = this->get_normal_pixmap();
    QIcon icon;

    icon.addPixmap(this->m_normal_pixmap,QIcon::Normal,QIcon::Off);
    icon.addPixmap(this->m_active_pixmap,QIcon::Active,QIcon::Off);
    icon.addPixmap(this->m_disabled_pixmap,QIcon::Disabled,QIcon::Off);
    icon.addPixmap(this->m_selected_pixmap,QIcon::Selected,QIcon::Off);

    setIcon(icon);
    setIconSize(pixmap.size());

    //如果按钮被按下，则重绘按钮图标
    if(this->isChecked())
    {
        paint_info(this->m_selected_pixmap);
    }

    //设置大小
    this->setMinimumWidth(46);
    QToolButton::paintEvent(event);
}


void ToolButton::paint_info(QPixmap pixmap)
{
    setIcon(pixmap);
    setIconSize(pixmap.size());
}


//normal
QPixmap ToolButton::get_normal_pixmap()
{
    return m_normal_pixmap;
}

void ToolButton::set_normal_pixmap(QPixmap pixmap)
{
    this->m_normal_pixmap = pixmap;
}

//active
QPixmap ToolButton::get_active_pixmap()
{
    return m_active_pixmap;
}

void ToolButton::set_active_pixmap(QPixmap pixmap)
{
    this->m_active_pixmap = pixmap;
}

//selected
QPixmap ToolButton::get_selected_pixmap()
{
    return m_selected_pixmap;
}

void ToolButton::set_selected_pixmap(QPixmap pixmap)
{
    this->m_selected_pixmap = pixmap;
}

//disabled
QPixmap ToolButton::get_disabled_pixmap()
{
    return m_disabled_pixmap;
}

void ToolButton::set_disabled_pixmap(QPixmap pixmap)
{
    this->m_disabled_pixmap = pixmap;
}
//hover
QPixmap ToolButton::get_hover_pixmap()
{
    return m_hover_pixmap;
}

void ToolButton::set_hover_pixmap(QPixmap pixmap)
{
    this->m_hover_pixmap = pixmap;
}

//pressed
QPixmap ToolButton::get_pressed_pixmap()
{
    return m_pressed_pixmap;
}

void ToolButton::set_pressed_pixmap(QPixmap pixmap)
{
    this->m_pressed_pixmap = pixmap;
}

//
QPixmap ToolButton::get_checked_pixmap()
{
    return m_checked_pixmap;
}

void ToolButton::set_checked_pixmap(QPixmap pixmap)
{
    this->m_checked_pixmap = pixmap;
}

//
QPixmap ToolButton::get_focus_pixmap()
{
    return m_focus_pixmap;
}

void ToolButton::set_focus_pixmap(QPixmap pixmap)
{
    this->m_focus_pixmap = pixmap;
}
