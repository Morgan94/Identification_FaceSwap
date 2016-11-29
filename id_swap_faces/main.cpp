#include "mainwindow.h"
#include "face_recognition.h"
#include <QApplication>

#include "face_detection.h"
#include "face_recognition.h"
#include "face_swap.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //const char* image1 = "/home/eleves/promo17/info/mlemiere/Documents/projet_intensif/Identification_multiple_et_substitution_de_visage/data/lemiere.jpg";
//    const char* image2 = "/home/eleves/promo17/info/mlemiere/Documents/projet_intensif/Identification_multiple_et_substitution_de_visage/data/gamaire.jpg";
//    const char* tmp = "/home/eleves/promo17/info/mlemiere/Documents/projet_intensif/Identification_multiple_et_substitution_de_visage/data/tmp.png";
//    const char* new_tmp = "/home/eleves/promo17/info/mlemiere/Documents/projet_intensif/Identification_multiple_et_substitution_de_visage/data/new_tmp.png";

    MainWindow w;
    w.show();
//    face_recognition *recog = new face_recognition("../Reconnaissance/learning.csv");
//    recog->learning();
//    int id = recog->predicting(cv::imread("../Reconnaissance/1.pgm",0));
//    cv::Mat pic = recog->get_reconizedPic(id);
//    cv::namedWindow("TEST", cv::WINDOW_NORMAL);
//    imshow("TEST", pic);
/*
    cv::Mat img1 = cv::imread(image1);
    std::vector<cv::Rect> faces1 = detect_objects(img1, Detectors::faces1);
    std::vector<cv::Rect> eyes1 = detect_objects(img1, Detectors::eye1);

    cv::Mat img2 = cv::imread(image2);
    std::vector<cv::Rect> faces2 = detect_objects(img2, Detectors::faces1);
    std::vector<cv::Rect> eyes2 = detect_objects(img2, Detectors::eye1);

    compute_mask(faces2[0],eyes2[0],eyes2[1],image2,tmp);

    cv::Mat tm = transformed_matrix(faces1[0],eyes1[0],eyes1[1],faces2[0],eyes2[0],eyes2[1]);
    modify_foreground(tmp,new_tmp,tm);

    face_swap(200,image1,new_tmp);
*/
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
