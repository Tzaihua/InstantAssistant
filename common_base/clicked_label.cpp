#include "clicked_label.h"

ClickedLabel::ClickedLabel(QWidget *parent): QLabel(parent),m_str("")
{
    setText(m_str);
}

ClickedLabel::~ClickedLabel()
{

}

void ClickedLabel::mouseReleaseEvent(QMouseEvent *event)
{
    QLabel::mouseReleaseEvent(event);
    emit Clicked(this);
}
