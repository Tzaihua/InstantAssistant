#include "function_button.h"

FunctionButton::FunctionButton(QWidget *parent) : QToolButton(parent)
{
    this->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//文本显示在图标旁边
    this->setAutoRaise(true);
    this->setContentsMargins(0,0,0,0);
}

FunctionButton::~FunctionButton()
{

}


void FunctionButton::paintEvent(QPaintEvent *event)
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
//    if(this->isChecked())
//    {
//        paint_info(this->m_selected_pixmap);
//    }

    //设置大小
    this->setMaximumHeight(24);//最大尺寸24px
    //去除按钮边框
    this->setStyleSheet(QStringLiteral("background:transparent;border:0px;"));

    //如果按钮没有文字，则只显示图标
    if(this->text().trimmed().length()== 0)
    {
        this->setToolButtonStyle(Qt::ToolButtonIconOnly);

    }
    QToolButton::paintEvent(event);
}


void FunctionButton::paint_info(QPixmap pixmap)
{
    setIcon(pixmap);
    setIconSize(pixmap.size());
}


//normal
QPixmap FunctionButton::get_normal_pixmap()
{
    return m_normal_pixmap;
}

void FunctionButton::set_normal_pixmap(QPixmap pixmap)
{
    this->m_normal_pixmap = pixmap;
}

//active
QPixmap FunctionButton::get_active_pixmap()
{
    return m_active_pixmap;
}

void FunctionButton::set_active_pixmap(QPixmap pixmap)
{
    this->m_active_pixmap = pixmap;
}

//selected
QPixmap FunctionButton::get_selected_pixmap()
{
    return m_selected_pixmap;
}

void FunctionButton::set_selected_pixmap(QPixmap pixmap)
{
    this->m_selected_pixmap = pixmap;
}

//disabled
QPixmap FunctionButton::get_disabled_pixmap()
{
    return m_disabled_pixmap;
}

void FunctionButton::set_disabled_pixmap(QPixmap pixmap)
{
    this->m_disabled_pixmap = pixmap;
}
//hover
QPixmap FunctionButton::get_hover_pixmap()
{
    return m_hover_pixmap;
}

void FunctionButton::set_hover_pixmap(QPixmap pixmap)
{
    this->m_hover_pixmap = pixmap;
}

//pressed
QPixmap FunctionButton::get_pressed_pixmap()
{
    return m_pressed_pixmap;
}

void FunctionButton::set_pressed_pixmap(QPixmap pixmap)
{
    this->m_pressed_pixmap = pixmap;
}

//
QPixmap FunctionButton::get_checked_pixmap()
{
    return m_checked_pixmap;
}

void FunctionButton::set_checked_pixmap(QPixmap pixmap)
{
    this->m_checked_pixmap = pixmap;
}

//
QPixmap FunctionButton::get_focus_pixmap()
{
    return m_focus_pixmap;
}

void FunctionButton::set_focus_pixmap(QPixmap pixmap)
{
    this->m_focus_pixmap = pixmap;
}
