#include "videodlg.h"
#include <QDebug>

videoDlg::videoDlg(QWidget *parent) : QDialog(parent)
{
    // 设置主界面
    setWindowTitle("视频教程");
    setFixedSize(560,580);

    layout = new QVBoxLayout();           // 全局的垂直布局
    videolayout = new QVBoxLayout();            // 视频的垂直布局
    viewPort = new QWidget();                   // 视频的视口
    scrollArea = new QScrollArea();             // 滚动区域

    // 加入视频

    addVideo("/Users/panda/Desktop/qt_project/TKA/src1/video/zhanweidunzixunlian.mp4", "站位蹲姿训练");
    addVideo("/Users/panda/Desktop/qt_project/TKA/src1/video/huaibeng1.mp4","踝泵运动1");
    addVideo("/Users/panda/Desktop/qt_project/TKA/src1/video/huaibeng2.mp4", "踝泵运动2");
    addVideo("/Users/panda/Desktop/qt_project/TKA/src1/video/zhanweihoutitui.mp4", "站位后踢腿训练");

    viewPort->setLayout(videolayout);
    scrollArea->setWidget(viewPort);          // 设置要滚动的区域
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    layout->addWidget(scrollArea);         // 滚动区域加入全局垂直布局
    setLayout(layout);

}

void videoDlg::addVideo(QString videoFilePath, QString title)
{
    // 创建一个播放器对象
    Player *player = new Player(videoFilePath, title);
    //std::shared_ptr<Player> player = std::make_shared<Player>(videoFilePath, title);

    // 创建一个播放控制器对象
    // 设置播放控制条
    playcontroler *m_playcontrol = new playcontroler(player);

    //std::shared_ptr<playcontroler> m_playcontroler = std::make_shared<playcontroler>(player.get());

    //m_playcontrol->setVolume(player.get()->m_AudioOutput->volume());
    // 将播放器对象添加到布局中

    videolayout->addWidget(player);

    // 将播放控制器对象添加到布局中
    videolayout->addWidget(m_playcontrol);

}

videoDlg::~videoDlg(){

}

