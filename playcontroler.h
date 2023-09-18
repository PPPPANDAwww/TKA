#ifndef PLAYCONTROLER_H
#define PLAYCONTROLER_H

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QComboBox>
#include <QToolButton>
#include <QStyle>
#include <QHBoxLayout>
#include <QLabel>
#include <QMediaPlayer>
#include <QTime>
#include <QAudio>
#include <memory>

QT_BEGIN_NAMESPACE
class Player;
class QAudioOutput;
QT_END_NAMESPACE

namespace Ui {
class playcontroler;
}

class playcontroler : public QWidget
{
    Q_OBJECT

public:
    playcontroler(Player *m_player, QWidget *parent = nullptr);
    void setVolume(float volume); // 设置音量
    ~playcontroler();

signals:
    void play();
    void pause();
    void changeVolume(float volume);

private slots:
    void playerstop();
    // 进度条相关
    void seek(int mseconds);
    void durationChanged(qint64 duration); // 更新时长
    void positionChanged(qint64 progress); // 更新位置

    // 按钮组相关
    void playClicked();
    void onVolumeSliderValueChanged(); // 静音


private:
    // std::unique_ptr<Player> player;
    Player *player = nullptr;
    QMediaPlayer *playerWindow = nullptr;
    QAudioOutput *audioOutput = nullptr;
    // std::unique_ptr<QMediaPlayer> playerWindow;
    // std::unique_ptr<QAudioOutput> audioOutput;
    QPushButton *stopBtn = nullptr;
    QPushButton *playBtn = nullptr;
    QPushButton *muteBtn = nullptr;
    QSlider *volumn_slider = nullptr;
    QComboBox *m_rateBox = nullptr;
    QSlider *m_slider = nullptr; // 进度条
    QLabel *m_labelDuration = nullptr; // 显示XX/XX进度
    qint64 m_duration; // 视频长度
    QMediaPlayer::PlaybackState m_playerState = QMediaPlayer::StoppedState; //  视频播放的状态
    bool m_mute = false;

    void updateDurationInfo(qint64 currentInfo); // 更新目前到的位置
    void updatePlayButton(); // 修改play按钮的UI
    void toggleMute(); // 设置静音键的功能和UI

    // 滑动条的刻度转化为音量
    float volume() const;

};

#endif // PLAYCONTROLER_H
