#include "library.h"

//функция считающая значение элемента свёртки по распределению коэфф Гаусса
double func_gaus(double devation,int x,int y){
    double pi = 3.1415926535;
    double st = (-1)*((x*x+y*y)/(2*devation));
    return (1/(2*pi*devation))*exp(st);
}

double filter(unsigned char*img2,int i, int j,int size_of_kernel,int dop_pix,int colour,int new_width,int channels,int new_height,int square_of_devation){

    //ядро для свёртки
    double filter_Gauss[size_of_kernel][size_of_kernel];
    memset(filter_Gauss, 0, sizeof(filter_Gauss));

    //заподняем ядро свёртки
    for(int k=0;k<size_of_kernel && (i+k)<new_height;k++){
        for(int h=0;h<size_of_kernel;h++){
            filter_Gauss[k][h] = func_gaus(square_of_devation,h-dop_pix,dop_pix-k);
        }
    }

    double sum=0;

    //применяем ядро
    for(int k=0;k<size_of_kernel && (i+k)<new_height;k++){
        for(int h=0;h<size_of_kernel;h++){
            sum+=(img2[((i+k)*new_width+(j+h))*channels+colour]*filter_Gauss[k][h]);
        }
    }
    return sum;
}

unsigned char* Gaussian_filter(unsigned char*initial_img, int width,int height,int channels,int size_of_kernel,int square_of_devation){

    //dop_pix это кол-во пикселей на которое нужно евеличить изображение, чтобы коректно обрабатывать пиксели находящиеся по краям
    int dop_pix = size_of_kernel/2;
    //ширина с учётом dop_pix
    int new_width=width+dop_pix;
    //высота с учётом dop_pix
    int new_height = height+dop_pix;

    //изображение, которое поступило на вход
    unsigned char *img = (unsigned char*)malloc(width*height*channels);
    memcpy(img, initial_img, width*height*channels);
    //увеличенное изображение для коректного применения свёрток
    unsigned char *img2 = Interpolation(img,width,height,channels,size_of_kernel,dop_pix,new_width,new_height);

    //проход по высоте
    for(int i=0; i<height;i++){
        //проход по ширине
        for(int j=0;j<width;j++){
            //проход по каналам
            for(int colour=0;colour<channels;colour++){
                img[(i*width+j)*channels+colour] = filter(img2,i,j,size_of_kernel,dop_pix,colour,new_width,channels,new_height,square_of_devation);
            }
        }
    }
    //очистка памяти
    free(img2);
    return img;
}