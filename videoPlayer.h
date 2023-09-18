#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>

namespace Ui {
class videoPlaer;
}

class videoPlaer : public QWidget
{
    Q_OBJECT

public:
    explicit videoPlaer(QWidget *parent = nullptr);
    ~videoPlaer();

};

#endif // VIDEOPLAYER_H
