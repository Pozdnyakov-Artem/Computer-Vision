#include "library.h"

/**
 * @brief функция считающая значение элемента свёртки по распределению коэфф Гаусса
 * 
 * @param devation постоянная Гаусса
 * @param x координата x в свёртке
 * @param y координата y в свёртке
 * 
 * @return int значение для свёртки по координатам (x,y)
 */
double func_gaus(double devation,int x,int y){
    double pi = 3.1415926535;
    double st = (-1)*((x*x+y*y)/(2*devation));
    return (1/(2*pi*devation))*exp(st);
}

/**
 * @brief наложение свёртки на изображение
 * 
 * @param img2 изображение
 * @param i расположение обрабатываемого пикселя по высоте
 * @param j расположение обрабатываемого пикселя по ширине
 * @param size_of_kernel длина стороны свёртки
 * @param dop_pix кол-во пикселей на которое нужно увеличить изображение с каждой стороны
 * @param colour канал изображения, который обрабатываем
 * @param new_width ширина нового изображения
 * @param channels кол-во каналов исходного изображения
 * @param new_height высота нового изображения
 * @param square_of_devation сигма для Гауссова фильтра
 * 
 * @return int новое значение пикселя 
 */
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

/**
 * @brief наложение границ на изображение
 * 1 создаём увеличенное изобрадение для применения свёртки
 * 2 применяем Гауссов фильтр
 * 
 * @param initial_img исходное изображение
 * @param width ширина исходного изображения
 * @param height высота исходного изображения
 * @param channels кол-во каналов исходного изображения
 * @param size_of_kernel длина стороны свёртки
 * @param square_of_devation сигма для Гауссова фильтра
 * 
 * @return указатель на новое изображение
 */

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