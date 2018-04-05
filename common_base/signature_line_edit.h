#ifndef SIGNATURELINEEDIT_H
#define SIGNATURELINEEDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QFocusEvent>
#include <QShowEvent>
#include <QCursor>
#include <QDebug>


class SignatureLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit SignatureLineEdit(QWidget *parent = 0);

    //个性签名输入框真实文本
    Q_PROPERTY(QString RealText READ getRealText WRITE setRealText NOTIFY RealTextChanged DESIGNABLE true)

    //个性签名输入框真实文本
    QString getRealText() const;
    QString real_text;

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);
    virtual void showEvent(QShowEvent *event);

private:
    //字符串省略号处理函数，功能将字体为font的字符串处理为当长度大于maxwidth时，大于部分显示为...
    QString long_str_to_truncate_by_ellipsis(QFont font, QString str, int max_width);

signals:
    void RealTextChanged(const QString str_text);
public slots:
    void setRealText(const QString str_text);

};

#endif // SIGNATURELINEEDIT_H
