#include <QApplication>
#include <QTranslator>
#include <QTextCodec>
#include <single_application.h>
#include <QMessageBox>
#include <QLibrary>


//#include "ctkPluginContext.h"
//#include "ctkPluginFramework.h"
//#include "ctkPluginFrameworkFactory.h"
//#include "ctkPluginException.h"
//#include "ctkPlugin.h"
//#include "ctkServiceReference.h"

#include "main_widget.h"


int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //单例化运行程序
    SingleApplication a(argc, argv);

    a.setOrganizationName("IAT");
    a.setOrganizationDomain("baizhihua.com");
    a.setApplicationName("InstantAssistantToolkits");
    a.setApplicationVersion("0.1.0");

//    //定义编码格式
//    QTextCodec *codec = QTextCodec::codecForName("System");

//    //这个函数的作用是设置传给tr函数时的默认字符串编码，GUI设计中最常用的一种。
//    //QTextCodec::setCodecForTr(utg8);

//    //这个函数主要用于设置和对本地文件系统读写时候的默认编码格式。比如通过流读取一个文件内容时的编码格式。或者通过qDebug（）输出打印信息时的编码。
//    QTextCodec::setCodecForLocale(codec);

    //一定要在界面的前面安装翻译器
    QTranslator translator;
    translator.load(QStringLiteral(":/resources/instant_assistant_zh_CN.qm"));
    a.installTranslator(&translator);

    //加载QSS样式表
    QFile qssStyleSheet(QStringLiteral(":/resources/default.qss"));
    //以只读方式打开
    if(!qssStyleSheet.open(QFile::ReadOnly)){
        qWarning("Can't open the style sheet file.");
    }
    a.setStyleSheet(qssStyleSheet.readAll());
    qssStyleSheet.close();


    //判断程序是否已经运行，如果没运行则启动程序
    if(!a.isRunning())
    {
        MainWidget w;//主窗体
        a.widget = &w;

        int login_widget_show_status = w.onCreateLoginScreen();
        if(login_widget_show_status == QDialog::Accepted)
        {
            w.onCreateSystemScreen();
            w.set_auto_run_by_regedit(false);//设置随操作系统自动启动
            return a.exec();
        }else
        {
            //当登录窗体关闭，等其它事件，可以直接退出程序
            a.quit();
            return 0;
        }

        QString app_path = QApplication::applicationDirPath();

        a.addLibraryPath(QString(app_path+"/plugins"));
        //a.addLibraryPath(QString("../plugins")); // 添加库路径

        return a.exec();
    }

    return 0;



}
