#include "player.h"

Player::Player(QString videoFilePath, QString title, QWidget *parent) :
    QWidget(parent)
{
    m_videoFilePath = videoFilePath;
    m_videoTitle = title;

    //  设置播放器
    m_player= new QMediaPlayer;
    // m_player = std::make_unique<QMediaPlayer>();
    m_player->setSource(QUrl::fromLocalFile(m_videoFilePath));

    // 设置视频播放界面
    videoWidget  = new QVideoWidget;
    videoWidget->setFixedSize(QSize(400, 300));
    //videoWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);// 设置为对话框的大小;
    m_player->setVideoOutput(videoWidget);

    //  设置音频播放
    m_AudioOutput = new QAudioOutput();
    // m_AudioOutput = std::make_unique<QAudioOutput>();
    m_player->setAudioOutput(m_AudioOutput);
    m_AudioOutput->setVolume(40);

    videoWidget->show();

    // 设置标签
    QVBoxLayout *videowithTileLayout = new QVBoxLayout;
    titleLabel = new QLabel(m_videoTitle);
    titleLabel->setAlignment(Qt::AlignCenter); // 设置标题居中对齐
    videowithTileLayout->addWidget(titleLabel);
    videowithTileLayout->addWidget(videoWidget);

    this->setLayout(videowithTileLayout);
}

Player::~Player()
{
    delete m_player;
}
