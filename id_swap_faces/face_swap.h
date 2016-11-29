#ifndef FACE_SWAP_H
#define FACE_SWAP_H

#include "global_inc.h"
#include "CImg.h"
#include "face_detection.h"

void compute_mask(cv::Rect face,cv::Rect eye1,cv::Rect eye2,const char* img1, const char* img2);
cv::Mat transformed_matrix(cv::Rect face1,cv::Rect eye11,cv::Rect eye12,cv::Rect face2,cv::Rect eye21,cv::Rect eye22);
void modify_foreground(const char* fg, const char* nfg, cv::Mat transformed_matrix);
void face_swap(int iteration_number, const char* img1, const char* img2);
void big_face_swap(const char* image);

#endif // FACE_SWAP_H
