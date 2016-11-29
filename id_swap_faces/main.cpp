#include "mainwindow.h"
#include "face_recognition.h"
#include <QApplication>

#include <opencv2/opencv.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    face_recognition *recog = new face_recognition("../test.csv");
//    recog->learning();
//    int id = recog->predicting(cv::imread("../Images/Trombino/faceRec/binet/binet.pgm",0));
//    COUT<<id<<ENDL;


    /*
    cv::Mat img = cv::imread("/home/eleves/promo17/info/cotinat/Images/Wallpapers/d3_wallpaper.png");
    cv::namedWindow("TEST");
    cv::imshow("TEST", img);
    */
    return a.exec();
}
