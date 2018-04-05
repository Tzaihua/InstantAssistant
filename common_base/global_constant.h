#ifndef GLOBAL_CONSTANT_H
#define GLOBAL_CONSTANT_H


const int WINDOW_SHADOW_WIDTH=5;       //窗体阴影宽度

const int MAIN_WINDOW_WIDTH=280;     //主窗体宽度
const int MAIN_WINDOW_HEIGHT=700;     //主窗体高度

const int MAIN_WIDGET_TAB_COUNT=6;       //主面板的Tab数据量,暂时没有使用

const int MAIN_PANNEL_LEFT_MARGIN=6;       //主面板左侧边距
const int MAIN_PANNEL_TOP_MARGIN=0;       //主面板顶部边距
const int MAIN_PANNEL_RIGHT_MARGIN=10;      //主面板右侧边距
const int MAIN_PANNEL_BOTTOM_MARGIN=4;       //主面板右侧边距

const int APP_MANAGER_WIDTH=722;     //应用管理器窗体宽度
const int APP_MANAGER_HEIGHT=558;     //应用管理器窗体高度

const int SETTING_PANNEL_WIDTH=700;//设置中心窗体宽度
const int SETTING_PANNEL_HEIGHT=510;//设置中心窗体高度

const int SETTING_PANNEL_TITLE_HEIGHT=30;//设置中心窗体标题区高度

const int SETTING_PANNEL_LEFT_LIST_WIDGET_WIDTH=130;//设置中心窗体左侧选项宽度

const int SETTING_PANNEL_RIGHT_SCROLL_AREA_CATEGORY_LABEL_WIDTH=100;//设置中心窗体,右下侧具体设置类别名称的宽度
const int SETTING_PANNEL_RIGHT_SCROLL_AREA_LEFT_MARGIN=36;//设置中心窗体,右下侧具体设置的左侧边距
const int SETTING_PANNEL_RIGHT_SCROLL_AREA_TOP_MARGIN=18;//设置中心窗体,右下侧具体设置的顶部边距
const int SETTING_PANNEL_RIGHT_SCROLL_AREA_SPACE=10;//设置中心窗体,右下侧具体设置控件的间隔

const int ABOUT_DIALOG_WIDTH=380;//关于对话框窗体宽度
const int ABOUT_DIALOG_HEIGHT=285;//关于对话框窗体高度

const int WEATHER_INFO_FLOATING_WIDGET_WIDTH=248;     //天气浮动窗体宽度
const int WEATHER_INFO_FLOATING_WIDGET_HEIGHT=238;     //天气浮动窗体高度

//主菜单
typedef enum{
    HELP_ONLINE,
    PLATFORM_HELP,
    LOGIN_HOME,
    PROTECT
}ACTION;

namespace Baijuhua {
    const QString APP_LICENSE_FILE = "LICENSE";//license存储目录
    const QString APP_PLUGINS_DIR = "plugins"; //程序插件目录
    const QString APP_CONFIG_DIR = "conf";//程序配置目录


    const int MINI_NEWS_WIDTH=750;     //迷你新闻弹出窗体宽度
    const int MINI_NEWS_HEIGHT=540;     //迷你新闻弹出窗体高度
}

#endif // GLOBAL_CONSTANT_H
