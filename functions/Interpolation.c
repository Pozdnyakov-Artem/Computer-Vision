#include "library.h"

unsigned char * Interpolation(unsigned char* img,int width, int height,int channels, int size_of_kernel,int dop_pix,int new_width,int new_height){

    //выделяем память под увеличенное изображение
    unsigned char *img2 = (unsigned char*)malloc((new_height)*(new_width)*channels);

    //проходим по высоте
    for(int i=0;i<new_height;i++){
        //проходим по ширине
        for(int j=0;j<new_width;j++){
            //проходим по каналам
            for(int colour=0;colour<channels;colour++){
                //обработка новых пикселей находящихся в левом верхнем углу 
                if(i<dop_pix && j < dop_pix){
                    img2[(i*new_width+j)*channels+colour]=img[0+colour];
                }
                //обработка новых пикселей находящихся с верху
                else if(i<dop_pix){
                    img2[(i*new_width+j)*channels+colour] = img[(0*width+(j-dop_pix))*channels+colour];
                }
                //обработка новых пикселей находящихся в правом верхнем углу
                else if(i<dop_pix && j>=width){
                    img2[(i*new_width+j)*channels+colour]=img[(0*width+(width-1))*channels+colour];
                }
                //обработка новых пикселей находящихся с правой стороны
                else if(i<height && j>=width){
                    img2[(i*new_width+j)*channels+colour]=img[((i-dop_pix)*width+(width-1))*channels+colour];
                }
                //обработка новых пикселей находящихся в правом нижнем углу
                else if(i>=height && j>=width){
                    img2[(i*new_width+j)*channels+colour]=img[((height-1)*width+(width-1))*channels+colour];
                }
                //обработка новых пикселей находящихся снизу
                else if(i>=height && j<width && j>=dop_pix){
                    img2[(i*new_width+j)*channels+colour]=img[((height-1)*width+(j-dop_pix))*channels+colour];
                }
                //обработка новых пикселей находящихся в левом нижнем углу
                else if(i>=height && j<dop_pix){
                    img2[(i*new_width+j)*channels+colour]=img[((height-1)*width+0)*channels+colour];
                }
                //обработка новых пикселей находящихся слева
                else if(i<height && j<dop_pix){
                    img2[(i*new_width+j)*channels+colour]=img[((i-dop_pix)*width+0)*channels+colour];
                }
                //перенос пикселей из изображения, которое увеличиваем
                else if(i>=dop_pix && i<height && j>=dop_pix && j<width){
                    img2[(i*new_width+j)*channels+colour] = img[((i-dop_pix)*width+(j-dop_pix))*channels+colour];
                }
            }
        }
    }
    return img2;
}