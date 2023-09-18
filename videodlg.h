#ifndef VIDEODLG_H
#define VIDEODLG_H

#include <QDialog>
#include <QMediaPlayer>
#include <QtMultimedia>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QAudioOutput>
#include <QScrollArea>
#include <QLabel>
#include "playcontroler.h"
#include "player.h"
#include <QList>
#include <memory>

QT_BEGIN_NAMESPACE
class Player;

QT_END_NAMESPACE

class videoDlg : public QDialog
{
    Q_OBJECT
public:
    explicit videoDlg(QWidget *parent = nullptr);
    ~videoDlg();
    QVBoxLayout * layout = nullptr; // 总体的垂直布局
    QScrollArea * scrollArea = nullptr; // 视频区域的滚动条
    QVBoxLayout * videolayout = nullptr; // 视频的垂直布局
    QWidget *viewPort = nullptr; //视频的展示区域
    //Player *player = nullptr;

private:
    void addVideo(QString videoFilePath, QString title);

};

#endif // VIDEODLG_H
