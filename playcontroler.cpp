#include "player.h"
#include <QAudioOutput>


playcontroler::playcontroler(Player *m_player, QWidget *parent) :
    QWidget(parent),
    player(m_player),
    playerWindow(m_player->m_player),
    audioOutput(m_player->m_AudioOutput)
{

    // 设置视频进度条
    m_slider = new QSlider(Qt::Horizontal, this);
    m_slider->setRange(0, playerWindow->duration());
    m_slider->show();
    m_slider->setStyleSheet("background-color: grey;");

    // 拖动进度条设置新的位置
    connect(m_slider, &QSlider::sliderMoved, this, &playcontroler::seek);

    // X.XX/10.00进度条标签
    m_labelDuration = new QLabel();
    m_labelDuration->show();

    // 根据标签的内容决定推荐的尺寸，标签的高度是不变的
    m_labelDuration->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    connect(playerWindow, &QMediaPlayer::durationChanged, this, &playcontroler::durationChanged);
    connect(playerWindow, &QMediaPlayer::positionChanged, this, &playcontroler::positionChanged);

    // 设置停止按钮
    stopBtn = new QPushButton("stop",this);
    stopBtn->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    connect(stopBtn, &QPushButton::clicked, playerWindow, &QMediaPlayer::stop);

    // 设置开始暂停按钮
    playBtn = new QPushButton("play",this);
    playBtn->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(playBtn, &QPushButton::clicked, this, &playcontroler::playClicked);
    connect(this, &playcontroler::play, playerWindow, &QMediaPlayer::play);
    connect(this, &playcontroler::pause, playerWindow, &QMediaPlayer::pause);
    connect(playerWindow, &QMediaPlayer::playbackStateChanged, this, &playcontroler::updatePlayButton);

    // 设置静音按钮
    muteBtn = new QPushButton("mute",this);
    muteBtn->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    connect(muteBtn, &QPushButton::clicked, this, &playcontroler::toggleMute);

    // 设置音量滑动条
    volumn_slider = new QSlider(Qt::Horizontal, this);
    volumn_slider->setRange(0, 60);
    connect(volumn_slider, &QSlider::valueChanged, this, &playcontroler::onVolumeSliderValueChanged);
    connect(this, &playcontroler::changeVolume, audioOutput, &QAudioOutput::setVolume);
    connect(audioOutput, &QAudioOutput::volumeChanged, this, &playcontroler::setVolume);

    // 设置倍速速率
    m_rateBox = new QComboBox(this);
    m_rateBox->addItem("0.5x", QVariant(0.5));
    m_rateBox->addItem("1.0x", QVariant(1.0));
    m_rateBox->addItem("2.0x", QVariant(2.0));
    m_rateBox->setCurrentIndex(1);

    // 整体布局
    QVBoxLayout* vLayout = new QVBoxLayout;
    // 播放停止控件组，开始停止音量静音
    QHBoxLayout* layout = new QHBoxLayout;
    // 进度条控件组，进度条+标签
    QHBoxLayout* silderlayout = new QHBoxLayout;

    silderlayout->addWidget(m_slider);
    silderlayout->addWidget(m_labelDuration);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(stopBtn);
    layout->addWidget(playBtn);
    layout->addWidget(muteBtn);
    layout->addWidget(volumn_slider);
    layout->addWidget(m_rateBox);

    vLayout->addLayout(silderlayout);
    vLayout->addLayout(layout);

    this->setLayout(vLayout);
}


playcontroler::~playcontroler()
{

}

void playcontroler::playerstop(){
    playerWindow->stop();
}

void playcontroler::seek(int mseconds){
    playerWindow->setPosition(mseconds);
}

// 进度条运行
void playcontroler::durationChanged(qint64 duration){
    // 转换成毫秒，duration单位是秒
    m_duration = duration / 1000;
    m_slider->setMaximum(duration);
}

// 更新位置
void playcontroler::positionChanged(qint64 progress){
    //  是否被按下，没有被按下正常进行运行
    if(!m_slider->isSliderDown()){
        m_slider->setValue(progress);
    }
    updateDurationInfo(progress/1000);
}

void playcontroler::updateDurationInfo(qint64 currentInfo){
    QString tStr;
    if(currentInfo || m_duration){
        QTime currentTime((currentInfo / 3600) % 60, (currentInfo / 60) % 60, currentInfo % 60, (currentInfo * 1000) % 1000);
        QTime totalTime((m_duration / 3600) % 60, (m_duration / 60) % 60, m_duration % 60, (m_duration * 1000) % 1000);
        QString format = "mm:ss";
        if(m_duration > 3600){
            format = "hh:mm:ss";
        }
        tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
    }
    m_labelDuration->setText(tStr);
    //qDebug() << "tStr is" << tStr;
}

void playcontroler::playClicked(){
    switch(m_playerState){
    case QMediaPlayer::StoppedState:
        emit play();
        m_playerState = QMediaPlayer::PlayingState;
        break;
    case QMediaPlayer::PausedState:
        emit play();
        m_playerState = QMediaPlayer::PlayingState;
        break;
    case QMediaPlayer::PlayingState:
        emit pause();
        m_playerState = QMediaPlayer::PausedState;
        playBtn->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        break;
    }
}

void playcontroler::updatePlayButton(){
    m_playerState = playerWindow->playbackState();
    if(m_playerState == QMediaPlayer::PlayingState)
    {
        playBtn->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        playBtn->setText("play");
    }else if(m_playerState == QMediaPlayer::PausedState)
    {
        playBtn->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        playBtn->setText("pause");
    }
}

void playcontroler::toggleMute(){
    if(!m_mute){
        // 设置静音
        m_mute = true;
        player->m_AudioOutput->setMuted(true);
        muteBtn->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        player->m_AudioOutput->setVolume(0);
    }else{
        m_mute = false;
        player->m_AudioOutput->setMuted(false);
        muteBtn->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        player->m_AudioOutput->setVolume(50);
    }
}

void playcontroler::onVolumeSliderValueChanged(){
    emit changeVolume(volume());
}

float playcontroler::volume() const{
    // 对数刻度转化为线性音量
    qreal linearVolume = QAudio::convertVolume(volumn_slider->value() / qreal(100),
                                               QAudio::LogarithmicVolumeScale,
                                               QAudio::LinearVolumeScale);
    return linearVolume;
}

void playcontroler::setVolume(float volume){
    // 线性音量转化为对数刻度(百分数)
    qreal LogarithmicVolume = QAudio::convertVolume(volume,
                                               QAudio::LinearVolumeScale,
                                               QAudio::LogarithmicVolumeScale);
    volumn_slider->setValue(qRound(LogarithmicVolume * 100));
}

