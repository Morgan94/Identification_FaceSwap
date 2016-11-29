#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include "opencv2/opencv.hpp"
#include <QMainWindow>
#include "face_recognition.h"

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

    void on_pb_imagePersonne_clicked();

    void on_pb_predict_clicked();

    void on_pb_personne1_clicked();

    void on_pb_personne2_clicked();

    void on_pb_swap_clicked();

private:
    Ui::MainWindow *ui;
    QImage _imdisplay;
    QTimer* _timer;
    cv::Mat _img;
    std::vector<cv::Rect> _objects;
    face_recognition *_rec;

    bool _detectionOK = false;
};

#endif // MAINWINDOW_H
