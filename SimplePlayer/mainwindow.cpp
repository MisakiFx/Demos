#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>

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
    //设置播放属性
    //1、监听信号变化
    connect(_mediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(MediaStateChanged(QMediaPlayer::State)));
    //2、播放进度变化函数
    connect(_mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(PositionChanged(qint64)));
    //3、媒体播放长度变化
    connect(_mediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(DurationChanged(qint64)));
    //4、设置播放错误关联
    connect(_mediaPlayer, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(HandleError()));
    //设置播放内容
    //_mediaPlayer->setMedia(QUrl::fromLocalFile("D:/KK/KK_Movies/1.mp4"));

    //设置播放按钮
    ui->pSButton->setToolTip("播放");//设置点击提示内容
    ui->pSButton->setAutoRaise(true);//设置自动弹起
    ui->pSButton->setEnabled(false);
    ui->pSButton->setIcon(QPixmap(":/image/play.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Play()
{
    //获取播放状态
    switch(_mediaPlayer->state())
    {
        case QMediaPlayer::PlayingState:
            _mediaPlayer->pause();
            break;
        default:
            _mediaPlayer->play();
            break;
    }
}

void MainWindow::on_pSButton_clicked()
{
    Play();

    //设置播放按钮暂停样式
//    ui->pSButton->setToolTip("暂停");
//    ui->pSButton->setIcon(QPixmap(":/image/stop.png"));
}

void MainWindow::MediaStateChanged(QMediaPlayer::State state)
{
    switch(state)
    {
        case QMediaPlayer::PlayingState:
            ui->pSButton->setToolTip("暂停");
            ui->pSButton->setIcon(QPixmap(":/image/stop.png"));
            break;
        default:
            ui->pSButton->setToolTip("播放");
            ui->pSButton->setIcon(QPixmap(":/image/play.png"));
            break;
    }
}

void MainWindow::PositionChanged(qint64 position)
{
    ui->playSlider->setValue(position);
}

void MainWindow::SetPositon(int position)
{
    _mediaPlayer->setPosition(position);
}

void MainWindow::DurationChanged(qint64 duration)
{
    ui->playSlider->setRange(0, duration);
}

void MainWindow::on_playSlider_sliderMoved(int position)
{
    if(_mediaPlayer->state() == QMediaPlayer::StoppedState)
    {
        ui->playSlider->setValue(0);
    }
    else
    {
        SetPositon(position);
    }
}

void MainWindow::HandleError()
{
    ui->pSButton->setEnabled(false);
}


void MainWindow::on_actionOpen_triggered()
{
    QString moviePath = QFileDialog::getOpenFileName(this, tr("Open Media"),
                                                     "/home",
                                                     tr("Media (*.mp4 *.wav *.mp3)"));
    _mediaPlayer->setMedia(QUrl::fromLocalFile(moviePath));
    ui->pSButton->setEnabled(true);
}
