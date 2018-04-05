#include "app_search_line_edit.h"


AppSearchLineEdit::AppSearchLineEdit(QWidget *parent):QLineEdit(parent)
{

    m_search_app_line_btn = new QPushButton();//搜索框图标按钮
    m_search_app_line_btn->setObjectName(QStringLiteral("m_search_app_line_btn"));
    m_search_app_line_btn->setCursor(Qt::PointingHandCursor);
    m_search_app_line_btn->setFixedSize(16,16);
    //Common::setButtonStyle(this->m_search_app_line_btn,QStringLiteral(":/resources/public/search/search_button.png"),4);

    QHBoxLayout *search_line_edit_layout = new QHBoxLayout();
    search_line_edit_layout->setSpacing(0);
    search_line_edit_layout->setContentsMargins(0,0,8,0);//设置搜索图标与边距
    search_line_edit_layout->addStretch(0);
    search_line_edit_layout->addWidget(m_search_app_line_btn);

    QMargins margin = this->textMargins();
    this->setTextMargins(margin.left(),margin.top(),m_search_app_line_btn->width()+8,margin.bottom());
    this->setLayout(search_line_edit_layout);

    //连接槽
    connect(m_search_app_line_btn,SIGNAL(clicked(bool)),this,SLOT(onSearch()));
    connect(this,SIGNAL(returnPressed()),this,SLOT(onSearch()));

}

void AppSearchLineEdit::onSearch()
{
    QString strSearch = this->text();
    if(!strSearch.isEmpty()){
        QMessageBox::information(this, QStringLiteral("search"), QStringLiteral("search:%1").arg(strSearch));
    }
}

