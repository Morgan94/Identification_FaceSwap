#ifndef FACE_RECOGNITION_H
#define FACE_RECOGNITION_H
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "global_inc.h"

#define COUT std::cout
#define ENDL std::endl

class face_recognition
{
public:
    face_recognition(const char* csvPath);
    void learning();
    int predicting(cv::Mat sample);
    cv::Mat get_reconizedPic(int predictedLabel);
private:
    cv::Mat norm_0_255(cv::InputArray _src);
    void read_csv(const char* filename, std::vector<cv::Mat>& images, std::vector<int>& labels, char separator = ';');
    const char* m_csvPath;
    const char* m_outputFolder;
    std::vector<cv::Mat> m_images;
    cv::Ptr<cv::FaceRecognizer> m_model;
};


#endif // FACE_RECOGNITION_H

