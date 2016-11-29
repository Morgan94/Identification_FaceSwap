#include "face_recognition.h"
// How to use me :
//    face_recognition *recog = new face_recognition("../test.csv");
//    recog->learning();
//    int id = recog->predicting(cv::imread("../Images/Trombino/faceRec/binet/binet.pgm",0));
//    COUT<<id<<ENDL;

using namespace cv;
using namespace std;

face_recognition::face_recognition(const char* csvPath)
{
    m_csvPath = csvPath;
    m_outputFolder = "../../recogOut";
}

// v function get on : http://docs.opencv.org/2.4/modules/contrib/doc/facerec/facerec_tutorial.html
 Mat face_recognition::norm_0_255(InputArray _src) {
    Mat src = _src.getMat();
    // Create and return normalized image:
    Mat dst;
    switch(src.channels()) {
    case 1:
        cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
        break;
    case 3:
        cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
        break;
    default:
        src.copyTo(dst);
        break;
    }
    return dst;
}

// v function get on : http://docs.opencv.org/2.4/modules/contrib/doc/facerec/facerec_tutorial.html
 void face_recognition::read_csv(const char* filename, vector<Mat>& images, vector<int>& labels, char separator) {
    std::ifstream file(filename, ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path,0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}
void face_recognition::learning()
{
    vector<int> labels;

    try {
            read_csv(m_csvPath, m_images, labels);
        } catch (cv::Exception& e) {
            cerr << "Error opening file \"" << m_csvPath << "\". Reason: " << e.msg << endl;
            exit(1);
        };

    for (int i=0; i<m_images.size() ;i++) {
        resize(m_images.at(i), m_images.at(i), Size(128,128));
    }
    m_model = createEigenFaceRecognizer();
    m_model->train(m_images, labels);
}

int face_recognition::predicting(Mat sample)
{
    resize(sample,sample,Size(128,128));
    return m_model->predict(sample);

}

cv::Mat face_recognition::get_reconizedPic(int predictedLabel)
{
    return m_images.at(predictedLabel);
}
