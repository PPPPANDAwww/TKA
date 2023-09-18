#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include "playcontroler.h"
#include <QVideoWidget>
#include <QAudioOutput>
#include <memory>


class Player : public QWidget
{
    Q_OBJECT

public:
    explicit Player(QString videoFilePath, QString title, QWidget *parent = nullptr);
    ~Player();

public:
    QMediaPlayer * m_player = nullptr;
    // std::unique_ptr<QMediaPlayer> m_player;
    QVideoWidget * videoWidget = nullptr;

    QAudioOutput * m_AudioOutput = nullptr;
    // std::unique_ptr<QAudioOutput> m_AudioOutput;
    QLabel *titleLabel = nullptr;
    QString m_videoFilePath;
    QString m_videoTitle;

};

#endif // PLAYER_H
