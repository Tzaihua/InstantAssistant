/*
 *Desc:SingleApplication 实现应用程序的单例启动
 *参考资料：http://www.cnblogs.com/js2854/archive/2014/04/24/qt-single-app.html?spm=5176.100239.blogcont47590.4.usKKPG
 *缺陷：
 * Author:Tzaihua
 * Date：2016年11月29日
 * Modify Date:
 * */

#ifndef SINGLEAPPLICATION_H
#define SINGLEAPPLICATION_H

#include <QObject>
#include <QApplication>
#include <QtNetwork/QLocalServer>
#include <QWidget>

class SingleApplication : public QApplication
{
    Q_OBJECT
public:
    SingleApplication(int &argc, char **argv);
    bool isRunning();                // 是否已经有实例在运行


public:
    QWidget *widget;

private slots:
    // 有新连接时触发
    void newLocalConnection();

private:
    // 初始化本地连接
    void initLocalConnection();
    // 创建服务端
    void newLocalServer();
    // 激活窗口
    void activateWindow();

private:
    bool is_running;                // 是否已经有实例在运行
    QLocalServer *local_server;     // 本地socket Server
    QString server_name;            // 服务名称

};

#endif // SINGLEAPPLICATION_H
