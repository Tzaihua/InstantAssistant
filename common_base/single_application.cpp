#include "single_application.h"

#include <QtNetwork/QLocalSocket>
#include <QFileInfo>

#define TIME_OUT                (500)    // 500ms

SingleApplication::SingleApplication(int &argc, char **argv)
    : QApplication(argc, argv)
    , widget(NULL)
    , is_running(false)
    , local_server(NULL) {

    // 取应用程序名作为LocalServer的名字
    server_name = QFileInfo(QCoreApplication::applicationFilePath()).fileName();

    initLocalConnection();
}


////////////////////////////////////////////////////////////////////////////////
// 说明：
// 检查是否已經有一个实例在运行, true - 有实例运行， false - 没有实例运行
////////////////////////////////////////////////////////////////////////////////
bool SingleApplication::isRunning() {
    return is_running;
}

////////////////////////////////////////////////////////////////////////////////
// 说明：
// 通过socket通讯实现程序单实例运行，监听到新的连接时触发该函数
////////////////////////////////////////////////////////////////////////////////
void SingleApplication::newLocalConnection() {
    QLocalSocket *socket = local_server->nextPendingConnection();
    if(socket) {
        socket->waitForReadyRead(2*TIME_OUT);
        delete socket;

        // 其他处理，如：读取启动参数

        activateWindow();
    }
}

////////////////////////////////////////////////////////////////////////////////
// 说明：
// 通过socket通讯实现程序单实例运行，
// 初始化本地连接，如果连接不上server，则创建，否则退出
////////////////////////////////////////////////////////////////////////////////
void SingleApplication::initLocalConnection() {
    is_running = false;

    QLocalSocket socket;
    socket.connectToServer(server_name);
    if(socket.waitForConnected(TIME_OUT)) {
        fprintf(stderr, "%s already running.\n",
                server_name.toLocal8Bit().constData());
        is_running = true;
        // 其他处理，如：将启动参数发送到服务端
        return;
    }

    //连接不上服务器，就创建一个
    newLocalServer();
}

////////////////////////////////////////////////////////////////////////////////
// 说明：
// 创建LocalServer
////////////////////////////////////////////////////////////////////////////////
void SingleApplication::newLocalServer() {
    local_server = new QLocalServer(this);
    connect(local_server, SIGNAL(newConnection()), this, SLOT(newLocalConnection()));
    if(!local_server->listen(server_name)) {
        // 此时监听失败，可能是程序崩溃时,残留进程服务导致的,移除之
        if(local_server->serverError() == QAbstractSocket::AddressInUseError) {
            QLocalServer::removeServer(server_name); // <-- 重点
            local_server->listen(server_name); // 再次监听
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// 说明：
// 激活主窗口
////////////////////////////////////////////////////////////////////////////////
void SingleApplication::activateWindow() {
    if(widget) {
        widget->show();
        widget->raise();
        widget->activateWindow(); // 激活窗口
    }
}
