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

    cvtColor(image, img_gray, COLOR_RGB2GRAY);
    equalizeHist(img_gray, img_gray);

    classif.detectMultiScale(img_gray, objects);

    return objects;
}

void draw_objects(Mat & image, const std::vector<Rect> objects){
    for (size_t i = 0; i < objects.size(); i++){
        rectangle(image, objects[i].tl(), objects[i].br(), cv::Scalar(0,255,0), 2);
    }
}

Mat get_draw_objects(const Mat & image, const std::vector<Rect> objects){
    Mat copy = image.clone();
    draw_objects(copy, objects);
    return copy;
}

std::vector<Mat> extract_square_image(Mat & image, std::vector<Rect> objects){
    std::vector<Mat> squares;

    for (size_t i = 0; i < objects.size(); i++){
        int size = (objects[i].width > objects[i].height) ? objects[i].width : objects[i].height;
        squares.push_back(image(Rect(objects[i].tl().x, objects[i].tl().y, size, size)).clone());
    }

    return squares;
}

void save_square_images(Mat & image, std::vector<Rect> objects, std::string directory){
    std::vector<Mat> squares = extract_square_image(image, objects);

    for (int i = 0; i < squares.size(); i++) {
        Mat save;
        resize(squares[i], save, Size(128,128));
        cvtColor(save, save, COLOR_RGB2GRAY);

        std::string dir = "mkdir " + directory + "/" + std::to_string(i);
        system(dir.c_str());

        imwrite(directory + "/" + std::to_string(i) + "/" "/img_" + std::to_string(i) + ".pgm", save);
    }
}

