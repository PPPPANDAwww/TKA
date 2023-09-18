#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "videoPlayer.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("膝康乐");
    QPixmap originalPixmap("://src1/icon/tka_cover.JPG");
    // Qt::KeepAspectRatio参数保持宽高比，Qt::SmoothTransformation参数可实现平滑的缩放效果。
    QPixmap scaledPixmap = originalPixmap.scaled(ui->coverLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->coverLabel->setPixmap(scaledPixmap);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_videoButton_clicked()
{
    // 初始化界面
    hide();
    videoDialog = new videoDlg(this);

    int res = videoDialog->exec();
    if(res == QDialog::Rejected){
        show();
        delete videoDialog;
    }

}

void MainWindow::on_imageButton_clicked()
{
    imagePage = new threedimage(this);
    imagePage->exec();
}

