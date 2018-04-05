#include "password_line_edit.h"

PasswordLineEdit::PasswordLineEdit(QWidget *parent):QLineEdit(parent)
{

    m_keyboard_btn = new QPushButton();//搜索框图标按钮
    m_keyboard_btn->setObjectName(QStringLiteral("m_keyboard_btn"));
    m_keyboard_btn->setCursor(Qt::PointingHandCursor);
    m_keyboard_btn->setFixedSize(20,20);

    QHBoxLayout *m_main_h_layout = new QHBoxLayout();
    m_main_h_layout->setSpacing(0);
    m_main_h_layout->setContentsMargins(0,0,8,0);//设置搜索图标与边距
    m_main_h_layout->addStretch(0);
    m_main_h_layout->addWidget(m_keyboard_btn);

    QMargins margin = this->textMargins();
    this->setTextMargins(margin.left(),margin.top(),m_keyboard_btn->width()+8,margin.bottom());
    this->setLayout(m_main_h_layout);

    //连接槽
    connect(m_keyboard_btn,SIGNAL(clicked(bool)),this,SIGNAL(virtualKeyboardClicked()));//虚拟键盘按钮被点击的信号
}

void PasswordLineEdit::onShowVirtualKeyboard()
{

}

void PasswordLineEdit::onHideVirtualKeyboard()
{

}
