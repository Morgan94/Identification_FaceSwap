#ifndef FACE_DETECTION_H
#define FACE_DETECTION_H

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <iostream>
#include <string>

enum Detectors{ faces, faces1, faces2, faces3, profile, eye, eye1 } ;
static std::string DetectorsString[] = {   "haarcascade_frontalface_default.xml",
                                           "haarcascade_frontalface_alt.xml",
                                           "haarcascade_frontalface_alt2.xml",
                                           "haarcascade_frontalface_alt_tree.xml",
                                           "haarcascade_profileface.xml",
                                           "haarcascade_eye.xml",
                                           "haarcascade_eye_tree_eyeglasses.xml"};

inline std::string getDetectorPath( Detectors detector)
{
  return "../../classifiers/" + DetectorsString[detector];
}


void detect_faces();

std::vector<cv::Rect> detect_objects(cv::Mat & image, Detectors detector);
void draw_objects(cv::Mat & image, std::vector<cv::Rect> objects);
std::vector<cv::Mat> extract_square_image(cv::Mat & image, std::vector<cv::Rect> objects);
void save_square_images(cv::Mat & image, std::vector<cv::Rect> objects, std::string directory);

#endif // FACE_DETECTION_H
