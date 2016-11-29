#include "face_swap.h"
#include "CImg.h"
#include <iostream>

#define MAX(a,b) ( (a) > (b) ? (a) : (b) )
#define ABS(a) ( (a) > 0 ? (a) : -(a) )


using namespace cimg_library;
using namespace cv;

// MASK DETERMINATION
// --------------------------------------------------------------
void compute_mask(Rect face,Rect eye1,Rect eye2,const char* img1, const char* img2){

    CImg<float> img(img1);
    CImg<float> foreground(img);
    CImg<float> mask(img);

    int I[9];
    int c;

    int lt1_x, lt1_y, rb1_x;
    int lt2_x, lt2_y, rb2_x;


    if(eye1.tl().x < eye2.tl().x){

        lt1_x = eye1.tl().x;
        lt1_y = eye1.tl().y;
        rb1_x = eye1.br().x;

        lt2_x = eye2.tl().x;
        lt2_y = eye2.tl().y;
        rb2_x = eye2.br().x;
    }
    else{

        lt1_x = eye2.tl().x;
        lt1_y = eye2.tl().y;
        rb1_x = eye2.br().x;

        lt2_x = eye1.tl().x;
        lt2_y = eye1.tl().y;
        rb2_x = eye1.br().x;
    }

    int frb_y = face.br().y;


    int m = ((rb1_x - lt1_x) + (rb2_x - lt2_x)) / 2 ; // mesure de base, correspond à la taille de l'oeil

    // définition de 4 points pour extraction.
    // proportions approximatives du visage
    int lt_x = lt1_x - m/3;
    int lt_y = lt1_y - m/2;

    int rt_x = rb2_x + m/3;
    int rt_y = lt2_y - m/2;

    int lb_x = lt1_x + m/2;
    int lb_y = frb_y - m/2;

    int rb_x = rb2_x - m/2;
    int rb_y = frb_y - m/2;


    cimg_forC(mask,c){
            cimg_for3x3(mask,x,y,0,c,I,float){
                  mask(x,y,0,c) = 0;
                  foreground(x,y,0,c) = 0;
            }
    }

    int white[] = {255,255,255};
    CImg<int> points(4,2);
    int coord[] = {lt_x,lt_y,rt_x,rt_y,rb_x,rb_y,lb_x,lb_y};
    int *iterator = coord;
    cimg_forX(points,i) {
        points(i,0) = *(iterator++);
        points(i,1) = *(iterator++);
    }
    mask.draw_polygon(points,white);


    cimg_forC(foreground,c){
        cimg_for3x3(foreground,x,y,0,c,I,float){

        if( mask(x,y,0,0) != 0 && mask(x,y,0,1) != 0 && mask(x,y,0,2) != 0)
            foreground(x,y,0,c) = img(x,y,0,c);
        }
    }
    foreground.save(img2);
    //(mask,img,foreground).display("Resultat");

    //return (lt1_y + lt2_y) /2;
}

// TRANSFORMED MATRIX
// ---------------------------------------------------------------
cv::Mat transformed_matrix(Rect face1,Rect eye11,Rect eye12,Rect face2,Rect eye21,Rect eye22){

    // calcul des points particuliers pour l'image 1
    Point2f img1[3];

    Rect tmp;
    if(eye11.tl().x > eye12.tl().x){
        tmp = eye11;
        eye11 = eye12;
        eye12 = tmp;
    }
    if(eye21.tl().x > eye22.tl().x){
        tmp = eye21;
        eye21 = eye22;
        eye22 = tmp;
    }


    img1[0].x = eye11.tl().x;
    img1[0].y = eye11.tl().y;
    img1[1].x = eye12.br().x;
    img1[1].y = eye12.tl().y;
    img1[2].x = (face1.br().x + face1.tl().x)/2;
    img1[2].y = face1.br().y;

    // calcul des points particuliers pour l'image 2
    Point2f img2[3];

    img2[0].x = eye21.tl().x;
    img2[0].y = eye21.tl().y;
    img2[1].x = eye22.br().x;
    img2[1].y = eye22.tl().y;
    img2[2].x = (face2.br().x + face2.tl().x)/2;
    img2[2].y = face2.br().y;


    /*int I[9];
    int c;
    CImg<float> imga("/home/eleves/promo17/info/mlemiere/Documents/projet_intensif/Identification_multiple_et_substitution_de_visage/data/diguet.jpg");
    CImg<float> imgb("/home/eleves/promo17/info/mlemiere/Documents/projet_intensif/Identification_multiple_et_substitution_de_visage/data/lemiere.jpg");

    cimg_forC(imga,c){
        cimg_for3x3(imga,x,y,0,c,I,float){

            if(((x==img1[0].x)&&(y==img1[0].y)) || ((x==img1[1].x)&&(y==img1[1].y)) || ((x==img1[2].x)&&(y==img1[2].y))){
                imga(x,y,0,c) = 255;
            }

            if(((x==img2[0].x)&&(y==img2[0].y)) || ((x==img2[1].x)&&(y==img2[1].y)) || ((x==img2[2].x)&&(y==img2[2].y))){
                imgb(x,y,0,c) = 255;
            }
        }
    }

    (imga,imgb).display("Resultat");*/

    return getAffineTransform(img2,img1);
}


// MODIFY FOREGROUND
// ---------------------------------------------------------------

void modify_foreground(const char* fg, const char* nfg, Mat transformed_matrix){


    Mat new_foreground = imread(fg);
    Mat foreground = imread(fg);
    Size s = foreground.size();
    warpAffine(foreground,new_foreground,transformed_matrix,s);

    imwrite(nfg,new_foreground);


    /*namedWindow("TEST", cv::WINDOW_NORMAL);
    imshow("TEST", new_foreground);
    waitKey(3000);*/
}



// FACE SWAP
// ---------------------------------------------------------------
void face_swap(int iteration_number, const char* img1, const char* img2) {


    CImg<float> B(img1);
    CImg<float> F(img2);
    CImg<float> didt(B);
    CImg<float> mask(F);
    CImg<float> GradBx(B.width(),B.height(),1,3);
    CImg<float> GradBy(B.width(),B.height(),1,3);
    CImg<float> GradFx(B.width(),B.height(),1,3);
    CImg<float> GradFy(B.width(),B.height(),1,3);
    CImg<float> Gradx(B.width(),B.height(),1,3);
    CImg<float> Grady(B.width(),B.height(),1,3);


    CImg<float> V(B.width(),B.height(),1,3);
    CImg<float> du1dx(B.width(),B.height(),1,3);
    CImg<float> du2dy(B.width(),B.height(),1,3);

    float Ixx,Iyy;
    float seuil = 5;

    int I[9];
    int c;

    // Calcul de l'image initiale pour le face swap
    cimg_forC(didt,c){
      cimg_for3x3(didt,x,y,0,c,I,float){

        if( F(x,y,0,0) >=5 && F(x,y,0,1) >=5 && F(x,y,0,2) >=5)
            didt(x,y,0,c) = F(x,y,0,c);
      }
    }

    // Mask
    cimg_forC(mask,c){
        cimg_for3x3(mask,x,y,0,c,I,float){

        if( F(x,y,0,0) != 0 && F(x,y,0,1) != 0 && F(x,y,0,2) != 0)
            mask(x,y,0,c) = 255;
        }
    }

    // Calcul des gradients des images
    cimg_forC(F,c){
      cimg_for3x3(F,x,y,0,c,I,float){

        GradFx(x,y,0,c) = (I[5] - I[3])/2;
        GradFy(x,y,0,c) = (I[7] - I[1])/2;

      }
    }
    cimg_forC(B,c){
      cimg_for3x3(B,x,y,0,c,I,float){

        GradBx(x,y,0,c) = (I[5] - I[3])/2;
        GradBy(x,y,0,c) = (I[7] - I[1])/2;

      }
    }
    mask.erode(6);
    cimg_forC(Gradx,c){
      cimg_for3x3(Gradx,x,y,0,c,I,float){
        if( mask(x,y,0,0) != 0 && mask(x,y,0,1) != 0 && mask(x,y,0,2) != 0){

            Gradx(x,y,0,c) = GradFx(x,y,0,c);
            Grady(x,y,0,c) = GradFy(x,y,0,c);
        }
        else{
            Gradx(x,y,0,c) = GradBx(x,y,0,c);
            Grady(x,y,0,c) = GradBy(x,y,0,c);
        }
      }
    }

    // Calcul des dérivés des gradients
    cimg_forC(Gradx,c){
        cimg_for3x3(Gradx,x,y,0,c,I,float){
            du1dx(x,y,0,c) = (I[5] - I[3])/2;
        }
    }

    cimg_forC(Grady,c){
        cimg_for3x3(Grady,x,y,0,c,I,float){
            du2dy(x,y,0,c) = (I[7] - I[1])/2;
        }
    }
    //(didt).display("init");

    // boucle iteration sur t, face swap
    for(int i=0;i<iteration_number;i++){

      cimg_forC(didt,c){
          cimg_for3x3(didt,x,y,0,c,I,float){

            Ixx = (I[5] + I[3]) - 2*I[4];
            Iyy = (I[7] + I[1]) - 2*I[4];

            V(x,y,0,c) = 2 * ((Ixx - du1dx(x,y,0,c) ) + (Iyy - du2dy(x,y,0,c)));
          }
      }

      // Calcul du dt adaptatif
      float Max,Min,Vmax,dt;
      Min = V.min_max(Max);
      Vmax = MAX(ABS(Min),ABS(Max));
      dt = seuil / Vmax;

      didt += dt * V;
      didt.cut(0,255);

    }
    (didt).display("Resultat");

}
