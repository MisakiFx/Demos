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
    void play();
    //获取播放状态
    void mediaStateChanged(QMediaPlayer::State state);
    //改变播放位置
    void positionChanged(qint64 position);
    //获取播放位置
    void setPositon(int position);
};

#endif // MAINWINDOW_H
