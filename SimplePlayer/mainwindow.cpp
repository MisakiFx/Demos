#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置主界面背景
//    QPixmap pixmap(":/image/background.jpg");
//    QPalette palette;
//    palette.setBrush(backgroundRole(), QBrush(pixmap));
//    setPalette(palette);
    ui->centralWidget->setStyleSheet("#centralWidget"
                                     "{"
                                     "border-image:url(:/image/background.jpg)"
                                     "}");

    //创建mediaPlayer
    _mediaPlayer = new QMediaPlayer(this);
    //设置对应mediaPlayer 的QVideoWidget
    _mediaPlayer->setVideoOutput(ui->videoWidget);

    //设置播放按钮
    ui->pSButton->setToolTip("播放");//设置点击提示内容
    ui->pSButton->setAutoRaise(true);//设置自动弹起
    ui->pSButton->setIcon(QPixmap(":/image/play.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
