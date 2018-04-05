#include "draggable_widget.h"


DraggableWidget::DraggableWidget(QWidget *parent) : QDialog(parent)
{
    //Qt::Tool，实现隐藏的任务栏图标，但是如果是最小化的话，会出现一个悬浮的小窗口，解决就是如果有托盘，那么点击最小化的时候你截取事件然后触发hide而不是最小化就好了。

    //去除窗体标题栏和边框,可在构造函数里面设备
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint );

    //设置窗体为透明
    this->setAttribute(Qt::WA_TranslucentBackground);


    //设置窗体初始为最大化
    //this->setWindowState(Qt::WindowMaximized);

    this->setMinimumHeight(MAIN_WINDOW_HEIGHT);
    this->setMinimumWidth(MAIN_WINDOW_WIDTH);


    //说明：http://blog.csdn.net/marlene0312/article/details/5221261
    //调用这个函数后，如想使mouseMoveEvent有效，也就是在鼠标在区域内移动就会触发，而非鼠标按键按下时才触发，注意只能是QWidget，如果是QMainwindow，则无效。
    this->setMouseTracking(true);

    //鼠标是否按下，初始化为false;
    this->isLeftPressDown = false;

    //显示在屏幕中央
    QRect desktop_rect = QApplication::desktop()->availableGeometry();
    this->move((desktop_rect.width() - this->width())/2, (desktop_rect.height() - this->height())/2);


}

void DraggableWidget::mousePressEvent(QMouseEvent *event){
    this->startPos = event->globalPos();//globalPos()，给出的坐标信息是相对于桌面的，即以桌面左上角为原点。
    this->clickPos = event->pos();//pos()，是相对于窗口的，以窗口左上角为原点（去除边框）。即pos()给出的是一个相对位置坐标。而globalPos(),给出的是一个绝对坐标。
    //判断是否是鼠标左键按下
    if(event->button() == Qt::LeftButton){
        if(event->type() == QEvent::MouseButtonPress){
            this->isLeftPressDown = true;
            event->accept();
        }
    }
    QWidget::mousePressEvent(event);
}

void DraggableWidget::mouseMoveEvent(QMouseEvent *event){
    QWidget::mouseMoveEvent(event);

    if(!isLeftPressDown){
        return;
    }
    this->move(event->globalPos() -  this->clickPos);
    this->update();//更新窗体样式
    event->accept();

}

void DraggableWidget::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton) {
        isLeftPressDown = false;


    }
    this->releaseMouse();
}

//绘制窗体边框阴影
void DraggableWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainterPath path;
    path.setFillRule(Qt::WindingFill);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    //判断窗体尺寸是否是与屏幕桌面的尺寸相同，并且窗体坐标的起始点是否是屏幕桌面起始点，如果都是，则边框Margin置为0
    if(this->geometry() == QApplication::desktop()->availableGeometry()
            && this->pos() == QPoint(0,0))
    {
        path.addRect(0, 0, this->width(), this->height());
        //painter.fillPath(path, QBrush(Qt::white));//原始代码
        painter.fillPath(path, QBrush(m_paint_background_color));//修改后的代码，主要实现QSS中，自定义属性
        painter.drawPath(path);
        this->setContentsMargins(0,0,0,0);
        qDebug()<<QStringLiteral("The base clase of MainWidow is max");
    }else
    {
        path.addRect(WINDOW_SHADOW_WIDTH, WINDOW_SHADOW_WIDTH, this->width()-WINDOW_SHADOW_WIDTH*2, this->height()-WINDOW_SHADOW_WIDTH*2);
        //painter.fillPath(path, QBrush(Qt::white));//原始代码
        painter.fillPath(path, QBrush(m_paint_background_color));//修改后的代码，主要实现QSS中，自定义属性
        QColor color(110, 110, 110, 50);//修改阴影颜色
        for(int i=0; i<WINDOW_SHADOW_WIDTH; i++)
        {
            QPainterPath path;
            path.setFillRule(Qt::WindingFill);
            path.addRect(WINDOW_SHADOW_WIDTH-i, WINDOW_SHADOW_WIDTH-i, this->width()-(WINDOW_SHADOW_WIDTH-i)*2, this->height()-(WINDOW_SHADOW_WIDTH-i)*2);
            color.setAlpha(100 - qSqrt(i)*50);
            painter.setPen(color);
            painter.drawPath(path);
        }
        this->setContentsMargins(WINDOW_SHADOW_WIDTH,WINDOW_SHADOW_WIDTH,WINDOW_SHADOW_WIDTH,WINDOW_SHADOW_WIDTH);
        qDebug()<<QStringLiteral("The base clase of MainWidow is normal");

    }


//    if(this->geometry() == QApplication::desktop()->availableGeometry()
//            && this->pos() == QPoint(0,0))
//    {
//        path.addRect(0, 0, this->width(), this->height());
//        painter.fillPath(path, QBrush(Qt::white));
//        painter.drawPath(path);
//        this->setContentsMargins(0,0,0,0);
//        qDebug()<<QStringLiteral("The base clase of MainWidow is max");
//    }else
//    {
//        path.addRect(5, 5, this->width()-10, this->height()-10);
//        painter.fillPath(path, QBrush(Qt::white));
//        QColor color(0, 0, 0, 50);
//        for(int i=0; i<5; i++)
//        {
//            QPainterPath path;
//            path.setFillRule(Qt::WindingFill);
//            path.addRect(5-i, 5-i, this->width()-(5-i)*2, this->height()-(5-i)*2);
//            color.setAlpha(100 - qSqrt(i)*50);
//            painter.setPen(color);
//            painter.drawPath(path);
//        }
//        this->setContentsMargins(5,5,5,5);
//        qDebug()<<QStringLiteral("The base clase of MainWidow is normal");

//    }


    //不具备最大化的检查功能，使用了上述方式进行了改进
//    if(this->isMaximized()){ //窗口最大化则不用绘制阴影
//        path.addRect(0, 0, this->width(), this->height());
//        painter.fillPath(path, QBrush(Qt::white));
//        painter.drawPath(path);
//        this->setContentsMargins(0,0,0,0);
//        qDebug()<<QStringLiteral("The base clase of MainWidow is max");

//    }else{
//        path.addRect(5, 5, this->width()-10, this->height()-10);
//        painter.fillPath(path, QBrush(Qt::white));
//        QColor color(0, 0, 0, 50);
//        for(int i=0; i<5; i++)
//        {
//            QPainterPath path;
//            path.setFillRule(Qt::WindingFill);
//            path.addRect(5-i, 5-i, this->width()-(5-i)*2, this->height()-(5-i)*2);
//            color.setAlpha(100 - qSqrt(i)*50);
//            painter.setPen(color);
//            painter.drawPath(path);
//        }
//        this->setContentsMargins(5,5,5,5);
//        qDebug()<<QStringLiteral("The base clase of MainWidow is normal");
//    }

}

QColor DraggableWidget::getPaintBackgroundColor() const
{
    return m_paint_background_color;

}


void DraggableWidget::setPaintBackgroundColor(const QColor paint_background_color)
{
    m_paint_background_color = paint_background_color;
    emit PaintBackgroundColorChanged(paint_background_color);//发改变信息

}
