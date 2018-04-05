#include "signature_line_edit.h"

SignatureLineEdit::SignatureLineEdit(QWidget *parent) : QLineEdit(parent)
{
    this->setMouseTracking(true);
    this->setFrame(true);
    this->setAutoFillBackground(true);
    this->setStyleSheet("QLineEdit{ background:rgba(0,0,0,0%); border:1px; font:10pt}"
                        "QLineEdit:hover{ border-image:url(:/resources/default/mainpannel/signature_line_edit/btn_background.png); }"
                        "QLineEdit:!hover{background:rgba(0,0,0,0%);}"
                        "QLineEdit:focus {background:white;border-image:none; border:1px groove lightgray; border-radius:2px}");

    this->real_text = this->text();//保存最初的文本

}


void SignatureLineEdit::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter - 1)
        this->clearFocus();

    QLineEdit::keyPressEvent(event);
}

void SignatureLineEdit::mousePressEvent(QMouseEvent *event)
{
    this->setFocus();
    this->setCursor(QCursor(Qt::IBeamCursor));
    QLineEdit::mousePressEvent(event);
}

void SignatureLineEdit::mouseMoveEvent(QMouseEvent *event)
{
    if(this->hasFocus())
    {
        this->setCursor(QCursor(Qt::IBeamCursor));
    }
    else
    {
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
    QLineEdit::mouseMoveEvent(event);
}

void SignatureLineEdit::mouseReleaseEvent(QMouseEvent *event)
{
    //
    QLineEdit::mouseReleaseEvent(event);
}

void SignatureLineEdit::focusOutEvent(QFocusEvent *event)
{
    if(this->hasFocus())
    {
        this->clearFocus();
    }
    QString str = long_str_to_truncate_by_ellipsis(this->font(),this->text(),this->width());
    this->setText(str);

    this->setCursorPosition(0);//光标在首位，QLineEdit也就从首位开始显示

    QLineEdit::focusOutEvent(event);
}

void SignatureLineEdit::showEvent(QShowEvent *event)
{
    //此处第一次提取的宽度不对，宽度要比失去焦点时提取的宽度大些，后面要修改
    QString str = long_str_to_truncate_by_ellipsis(this->font(),this->text(),this->width());
    this->setText(str);

    this->setCursorPosition(0);//光标在首位，QLineEdit也就从首位开始显示

    QLineEdit::showEvent(event);
}

QString SignatureLineEdit::getRealText() const
{
    return this->real_text;
}

void SignatureLineEdit::setRealText(const QString str_text)
{
    this->real_text = str_text;

    emit RealTextChanged(str_text);
}


/*****************************************
*字符串省略号处理函数，功能将字体为font的字符串
* 处理为当长度大于maxwidth时，大于部分显示为...
* 参考：http://blog.csdn.net/a379840689/article/details/41088735
*****************************************/
///
/// \brief SignatureLineEdit::long_str_to_truncate_by_ellipsis
/// \param font 字符串字体
/// \param str  要处理的字符串
/// \param max_width    字符串最大宽度
/// \return 返回处理后的字符串
///
///
QString SignatureLineEdit::long_str_to_truncate_by_ellipsis(QFont font, QString str, int max_width)
{
    this->setRealText(str);//在处理字符串前，先将原始字符串保存

    QFontMetrics fontWidth(font);
    int width = fontWidth.width(str);  //计算字符串宽度
    qDebug()<<"eg:width of abcdefg"<<fontWidth.width("abcdefg...");  //qDebug获取"abcdefg..." 为60
    if(width>=max_width)  //当字符串宽度大于最大宽度时进行转换
    {
        str = fontWidth.elidedText(str,Qt::ElideRight,max_width);  //右部显示省略号
    }
    return str;   //返回处理后的字符串
}
