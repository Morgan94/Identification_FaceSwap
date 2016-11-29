#include "mainwindow.h"
#include <QApplication>

#include "face_detection.h"
#include "face_recognition.h"
#include "face_swap.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

/*
    cv::Mat img = cv::imread("/home/eleves/promo17/info/cotinat/Documents/3A/data/promo.jpg");
    std::vector<cv::Rect> faces = detect_objects(img, Detectors::faces);
    draw_objects(img, faces);

    cv::namedWindow("TEST", cv::WINDOW_NORMAL);
    imshow("TEST", img);
*/
    return a.exec();
}
