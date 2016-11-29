#include "mainwindow.h"
#include <QApplication>

#include <opencv2/opencv.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    /*
    cv::Mat img = cv::imread("/home/eleves/promo17/info/cotinat/Images/Wallpapers/d3_wallpaper.png");
    cv::namedWindow("TEST");
    cv::imshow("TEST", img);
    */
    return a.exec();
}
