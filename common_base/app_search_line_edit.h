/*!
  *@file
  *@brief   为搜索框添加搜索图标
  *@author  Tzaihua
  *@date    2016-12-15
  */


#ifndef APPSEARCHLINEEDIT_H
#define APPSEARCHLINEEDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QEvent>
#include <QFocusEvent>
#include <QMouseEvent>

#include "common.h"

class AppSearchLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    AppSearchLineEdit(QWidget *parent = 0);
protected:
    QPushButton *m_search_app_line_btn;//搜索按钮
    QHBoxLayout *search_line_edit_layout;//搜索框架的整体布局

public slots:
    void onSearch();


};

#endif // APPSEARCHLINEEDIT_H
