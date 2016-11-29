#include "mainwindow.h"
#include <QApplication>

#include "face_detection.h"
#include "face_recognition.h"
#include "face_swap.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    //face_swap(200);
    //mask(92,232,153,260,186,219,248,257,72,177,291,402);
    //mask(108,182,160,192,204,166,252,191,89,142,264,332);


    cv::Mat img = cv::imread("/home/eleves/promo17/info/mlemiere/Documents/projet_intensif/Identification_multiple_et_substitution_de_visage/data/gamaire.jpg");
    std::vector<cv::Rect> faces = detect_objects(img, Detectors::faces);
    draw_objects(img, faces);

    cv::namedWindow("TEST", cv::WINDOW_NORMAL);
    imshow("TEST", img);

    return a.exec();
}
