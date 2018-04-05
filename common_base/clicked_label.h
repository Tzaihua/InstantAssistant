/*!
  *@file
  *@brief   用于超链接
  *@author  Tzaihua
  *@date    2017-01-27
  */
#ifndef CLICKED_LABEL_H
#define CLICKED_LABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>

class ClickedLabel : public QLabel
{
    Q_OBJECT
public:
    ClickedLabel(QWidget *parent=0);
    ~ClickedLabel();

protected:
    void mouseReleaseEvent( QMouseEvent* event);
private:
    QString m_str;
signals:
    void Clicked(ClickedLabel* clicked);


};

#endif // CLICKED_LABEL_H
