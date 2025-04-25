#include "library.h"

/**
 * @brief наложение границ на изображение
 * 1 находим границ
 * 2 накладываем границы на изображение
 * 
 * @param img исходное изображение
 * @param width ширина исходного изображения
 * @param height высота исходного изображения
 * @param channels кол-во каналов исходного изображения
 * @param size_of_kernel длина стороны свёртки
 * @param square_of_devation сигма для Гауссова фильтра
 * 
 * @return указатель на новое изображение
 */

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