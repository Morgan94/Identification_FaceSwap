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


    /*
    cv::Mat img = cv::imread("/home/eleves/promo17/info/cotinat/Documents/3A/data/trombi1.png");

    std::vector<cv::Rect> obj_faces = detect_objects(img, Detectors::faces);
    //draw_objects(img, faces);
    std::vector<cv::Mat> faces = extract_square_image(img, obj_faces);

    cv::namedWindow("TEST", cv::WINDOW_NORMAL);
    for (int i = 0; i < faces.size(); i++) {
        imshow("TEST", faces[i]);
        cvWaitKey(2000);
    }

    save_square_images(img, obj_faces, "/home/eleves/promo17/info/cotinat/Documents/3A/data/pgm");
    */

    return a.exec();
}
