#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QButtonGroup"
#include "QDialog"
#include "QPixmap"
#include "videodlg.h"
#include "threedimage.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_videoButton_clicked();
    void on_imageButton_clicked();

private:
    Ui::MainWindow *ui;
    videoDlg *videoDialog;
    threedimage *imagePage;

};
#endif // MAINWINDOW_H
