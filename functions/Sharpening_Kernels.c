#include "library.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../libs/stb_image.h"
#include "../libs/stb_image_write.h"

/**
 * @brief функция для наложения ядра свёртки, которое повышает резкость
 * 
 * @param i расположение обрабатываемого пикселя по высоте
 * @param j расположение обрабатываемого пикселя по ширине
 * @param img изображение
 * @param dop_pix кол-во пикселей на которое нужно увеличить изображение с каждой стороны
 * @param channels кол-во каналов исходного изображения
 * @param colour канал изображения, который обрабатываем 
 * @param width ширина изображения
 * 
 * @return int новое значение пикселя
 */
int Sharp(int i, int j, unsigned char* img,int size_of_kernel,int dop_pix,int channels,int colour,int width){

    //ядро свёртки для повышения резкости
    double kernel[size_of_kernel][size_of_kernel];
    memset(kernel,0,sizeof(kernel));
    
    kernel[0][1] = -0.1;
    kernel[1][0] = -0.1;
    kernel[1][2] = -0.1;
    kernel[2][1] = -0.1;
    kernel[1][1] = 1.4;

    int sum=0;

    //наложение ядра
    for(int k=i-dop_pix;k<(i+dop_pix);k++){
        for(int h=j-dop_pix;h<(j+dop_pix);h++){
            sum+=(img[(k*width+h)*channels+colour]*kernel[k-i+dop_pix][h-j+dop_pix]);
        }
    }

    if(sum>255){
        sum=255;
    }
    else if(sum<0){
        sum=0;
    }

    return sum;
}


/**
 * @brief увеличение резкости изображения
 * 1 накладываем ядро свёртки
 * 
 * @param img исходное изображение
 * @param width ширина исходного изображения
 * @param height высота исходного изображения
 * @param channels кол-во каналов исходного изображения
 * 
 * @return указатель на новое изображение
 */
unsigned char* Sharpening_Kernels(unsigned char*img, int width, int height, int channels){

    //новое изображение
    unsigned char*imgE = (unsigned char*)malloc(width*height*channels);

    //длина стороны свёртки
    int size_of_kernel = 3;
    //dop_pix это кол-во пикселей на которое нужно евеличить изображение, чтобы коректно обрабатывать пиксели находящиеся по краям
    int dop_pix = size_of_kernel/2;

    //применение ядра
    for(int i=1;i<height-1;i++){
        for(int j=1;j<width-1;j++){
            for(int colour=0;colour<channels;colour++){
                imgE[(i*width+j)*channels+colour] = Sharp(i,j,img,size_of_kernel,dop_pix,channels,colour,width);
            }
        }
    }

    return imgE;
}