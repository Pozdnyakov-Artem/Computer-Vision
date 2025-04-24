#include "library.h"

unsigned char* bord_on_img(unsigned char*img, int width, int height, int channels,int size_of_kernel,int square_of_devation){

    //новое изображение
    unsigned char *brd_img = (unsigned char*)malloc(width*height*channels);
    
    //вызов детектора границ Кэнни для определения границ
    brd_img = Canny_Edge_Detector(img,width,height,channels,size_of_kernel,square_of_devation);

    //наложение границ на исходное изображение
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            for(int colour=0;colour<channels;colour++){
                if(brd_img[(i*width+j)*channels+colour]<img[(i*width+j)*channels+colour]){
                    brd_img[(i*width+j)*channels+colour] = img[(i*width+j)*channels+colour];
                }
            }
        }
    }

    return brd_img;
}