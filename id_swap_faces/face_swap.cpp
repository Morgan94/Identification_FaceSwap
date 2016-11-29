#include "face_swap.h"
#include "CImg.h"
#include <iostream>

#define MAX(a,b) ( (a) > (b) ? (a) : (b) )
#define ABS(a) ( (a) > 0 ? (a) : -(a) )


using namespace cimg_library;


// MASK DETERMINATION
// --------------------------------------------------------------
void mask(int lt1_x, int lt1_y,int rb1_x,int rb1_y, int lt2_x, int lt2_y,int rb2_x,int rb2_y, int flt_x, int flt_y, int frb_x, int frb_y){

    CImg<float> face("/home/eleves/promo17/info/mlemiere/Documents/projet_intensif/Identification_multiple_et_substitution_de_visage/data/gamaire.jpg");
    CImg<float> foreground(face);
    CImg<float> mask(face);
    int m = ((rb1_x - lt1_x) + (rb2_x - lt2_x)) / 2 ; // mesure de base, correspond à la taille de l'oeil
    int I[9];
    int c;

    // définition de 4 points pour extraction.
    int lt_x = lt1_x - m/4;
    int lt_y = lt1_y - m/2;

    int rt_x = rb2_x + m/4;
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
            foreground(x,y,0,c) = face(x,y,0,c);
        }
    }
    foreground.save("/home/eleves/promo17/info/mlemiere/Documents/projet_intensif/Identification_multiple_et_substitution_de_visage/data/foreground1.ppm");
    (mask,face,foreground).display("Resultat");


}

// FACE SWAP
// ---------------------------------------------------------------
void face_swap(int iteration_number) {


    CImg<float> F("/home/eleves/promo17/info/mlemiere/Documents/projet_intensif/Identification_multiple_et_substitution_de_visage/data/foreground1.ppm");
    CImg<float> B("/home/eleves/promo17/info/mlemiere/Documents/projet_intensif/Identification_multiple_et_substitution_de_visage/data/lacherez.jpg");
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

        if( F(x,y,0,0) != 0 && F(x,y,0,1) != 0 && F(x,y,0,2) != 0)
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
    mask.erode(3);
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
