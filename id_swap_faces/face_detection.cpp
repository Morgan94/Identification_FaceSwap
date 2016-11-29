#include "face_detection.h"

using namespace cv;

std::vector<Rect> detect_objects(Mat & image, Detectors detector){
    std::vector<Rect> objects;
    Mat img_gray;

    CascadeClassifier classif = CascadeClassifier(getDetectorPath(detector));
    if(classif.empty())
    {
        std::cout << "Erreur de chargement du fichier XML du classifieur" << std::endl;
        return objects;
    }

    cvtColor(image, img_gray, COLOR_BGR2GRAY);
    equalizeHist(img_gray, img_gray);

    classif.detectMultiScale(img_gray, objects);

    return objects;
}

void draw_objects(Mat & image, std::vector<Rect> objects)
{
    for (size_t i = 0; i < objects.size(); i++){
        rectangle(image, objects[i].tl(), objects[i].br(), cv::Scalar(0,255,0), 2);
    }
}





