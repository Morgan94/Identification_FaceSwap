#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include "opencv2/opencv.hpp"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void DisplayImage(QString path);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void DisplayImage(cv::Mat img);

private slots:
    void on_pb_file_clicked();
    void on_pb_folder_clicked();

    void on_pb_detection_clicked();

    void on_pb_arb_clicked();

    void on_pb_clear_clicked();

private:
    Ui::MainWindow *ui;
    QImage _imdisplay;
    QTimer* _timer;
    cv::Mat _img;
    std::vector<cv::Rect> _objects;

    bool _detectionOK = false;
};

#endif // MAINWINDOW_H
