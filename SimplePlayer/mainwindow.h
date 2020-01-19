#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVideoWidget>
#include <QMediaPlayer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMediaPlayer* _mediaPlayer;

private slots:
    //播放
    void Play();
    //播放过程中动态调整播放进度
    void MediaStateChanged(QMediaPlayer::State state);
    //改变播放位置
    void PositionChanged(qint64 position);
    //设置进度条调整位置
    void SetPositon(int position);
    //设置进度条范围
    void DurationChanged(qint64 duration);
    //播放异常的抛出
    void HandleError();

    //开始暂停按钮
    void on_pSButton_clicked();
    //进度条
    void on_playSlider_sliderMoved(int position);
    //菜单栏
    void on_actionOpen_triggered();
};

#endif // MAINWINDOW_H
